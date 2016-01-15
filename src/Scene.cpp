#include "Scene.hpp"

#include "GUI/GUIElements.hpp"

#include "irrlicht.h"

#include <iostream>

namespace ic = irr::core;
namespace iv = irr::video;

//Constructor
Scene::Scene()
{
    // display values
    m_wind_speed      = 20;
    m_altitude        = 1000;
    m_vertical_speed  = -20;
    m_gauge_offset    = 0;
    m_stall          = true;

    m_planeSpeed    = 0.0f;
    m_planeAltitude = 0.0f;
    m_rotAngle      = 0.0f;
}

void Scene::initializeIrrlicht()
{
    // Event manager
    m_receiver = new EventReceiver();

    // Window and rendering system creation
    m_device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d<u32>(640, 480),
                                          16, false, false, false, m_receiver);
    m_driver = m_device->getVideoDriver();
    m_smgr  = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();

    m_device->getFileSystem()->addFileArchive("data.zip");
}

void Scene::initializeObjects()
{
    //City
    City* city = new City(m_smgr, "data/city/city_cercles.obj");
    city->initialize();

    //Init the object plane
    //2 parents: trajectory and rotation
    m_parentNode = m_smgr->addEmptySceneNode();
    m_parentRotationNode = m_smgr->addEmptySceneNode();
    m_parentRotationNode->setParent(m_parentNode);

    //Init the plane
    m_body = new Body(m_smgr, m_parentRotationNode, "data/plane/plane.obj");
    m_body->initialize();

    //Init the screw
    m_screw = new Screw(m_smgr, m_parentRotationNode, "data/plane/screw.obj");
    m_screw->initialize();

    //Init the two wings
    m_leftWing = new Wing(m_smgr, m_parentRotationNode,"data/plane/leftWing.obj");
    m_leftWing->setPosition(ic::vector3df(-0.667,0.303,0.19));
    m_leftWing->initialize();
    m_rightWing = new Wing(m_smgr, m_parentRotationNode,"data/plane/rightWing.obj");
    m_rightWing->setPosition(ic::vector3df(0.667,0.303,0.19));
    m_rightWing->initialize();

    //Init the three tails
    m_middleTail = new Tail(m_smgr, m_parentRotationNode, "data/plane/tail.obj");
    m_middleTail->setPosition(ic::vector3df(0.001,0.355,-0.53));
    m_middleTail->initialize();
    m_leftTail = new Tail(m_smgr, m_parentRotationNode, "data/plane/leftTail.obj");
    m_leftTail->setPosition(ic::vector3df(-0.205,0.23,-0.441));
    m_leftTail->initialize();
    m_rightTail = new Tail(m_smgr, m_parentRotationNode, "data/plane/rightTail.obj");
    m_rightTail->setPosition(ic::vector3df(0.208,0.225,-0.441));
    m_rightTail->initialize();

    //Water
    Water* water = new Water(m_smgr, m_driver->getTexture("data/water/water.jpg"));
    water->initialize();

    //Fire
    m_fire = new Fire(m_smgr, m_driver->getTexture("data/fire/fire.jpg"));
    m_fire->initialize();

    // Collision management with surroundings
    manageCollisionsWithSurroundings(city->getMesh(), city->getNode());
}
void Scene::initializeGui()
{
    // GUI elements mananger
    m_guiManager = new GUIElements();
    m_guiManager->setDevice(m_device);

    // 2D elements initialization
    m_guiManager->initialize2DElements();
}

void Scene::manageCollisionsWithSurroundings(irr::scene::IMesh *surroundingMesh, irr::scene::ISceneNode* surroundingNode)
{
    scene::ITriangleSelector *selectorSurrounding;
    selectorSurrounding = m_smgr->createOctreeTriangleSelector(surroundingMesh, surroundingNode);
    surroundingNode->setTriangleSelector(selectorSurrounding);

    m_animCollision = m_smgr->createCollisionResponseAnimator(selectorSurrounding,
                                                 m_parentNode,  //Node
                                                 ic::vector3df(2.8, 0.5, 0.4), // Ellipse dimensions
                                                 ic::vector3df(0, 0, 0),       // Gravity
                                                 ic::vector3df(1.0,0,0));      // Gap with the center
    m_parentNode->addAnimator(m_animCollision);
    m_animCollision->drop();
}

void Scene::initializeData()
{
    initializeGui();
    initializeObjects();

}

void Scene::render()
{
    //Update 2D elements
    std::vector<CGUICompass*> compasses = m_guiManager->update2DElements();

    //Detection of collisions
    ic::vector3df firePosition = ic::vector3df(0.0,-0.1,3.);
    m_fire->getPs()->setPosition(m_parentNode->getPosition() + firePosition); //position of the fire particules

    //If the plane is flying then
    //  inFlight = true
    //Else, ie. plane on the ground, in take-off position and in landing position
    //  inFlight = false
    ic::vector3df rotation = m_parentNode->getRotation();
    ic::vector3df position = m_parentNode->getPosition();

    if(m_animCollision->collisionOccurred() == true)
    {
        m_receiver->setIsCrashed(true);
    }

    if(m_receiver->getOnFloor())
    {
        m_receiver->planeOnFloor(m_parentRotationNode);

        rotation.Y      = m_receiver->getRotation();
        m_planeSpeed      = m_receiver->getSpeed();

        position.X += m_planeSpeed * sin(rotation.Y * M_PI / 180.0);
        position.Z += m_planeSpeed * cos(rotation.Y * M_PI / 180.0);
    }
    else if(m_receiver->getInTakeOff())
    {
        //std::cout<<"TD : plane is taking off"<<std::endl;
    }
    else if(m_receiver->getInFlight() && !m_receiver->getIsCrashed())
    {
        // Update screw rotation
        m_screw->updateRotation();

        m_receiver->planeInFlight(m_parentRotationNode, m_leftWing->getNode(), m_rightWing->getNode(), m_middleTail->getNode(), m_leftTail->getNode(), m_rightTail->getNode());


        rotation.Y      = m_receiver->getRotation();
        m_planeSpeed      = m_receiver->getSpeed();
        m_planeAltitude   = m_receiver->getAltitude();

        position.X += m_planeSpeed * sin(rotation.Y * M_PI / 180.0);
        position.Z += m_planeSpeed * cos(rotation.Y * M_PI / 180.0);
        position.Y  = m_planeAltitude;

        std::cout<<"kbfkdjqs"<<std::endl;
    }
    else if(m_receiver->getInLanding())
    {
        //std::cout<<"TD : plane is landing"<<std::endl;
    }
    else if(m_receiver->getIsStalling())
    {
        //std::cout<<"TD : the plane is stalling"<<std::endl;
    }
    else if(m_receiver->getIsCrashed())
    {
        firePosition.X = m_animCollision->getCollisionPoint().X;
        firePosition.Y = m_animCollision->getCollisionPoint().Y;
        firePosition.Z = m_animCollision->getCollisionPoint().Z;
        m_fire->getPs()->setEmitter(m_fire->getEm()); // this grabs the emitter of fire particules

        //std::cout<<"TD : the plane has crashed"<<std::endl;
    }

    m_parentNode->setRotation(rotation);
    m_parentNode->setPosition(position);

    //Camera position
    m_smgr->addCameraSceneNode(m_body->getNode(), ic::vector3df(0, 5, -34), m_parentNode->getPosition()); //0,5,-34

    //Back color
    m_driver->beginScene(true,true,iv::SColor(100,150,200,255));

    // Draw the scene
    m_smgr->drawAll();
    m_gui->drawAll();

    for(unsigned int i = 0; i < compasses.size(); i++)
    {
        compasses[i]->draw();
    }

    m_driver->endScene();
}


