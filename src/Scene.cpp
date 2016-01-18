#include "Scene.hpp"

#include "GUI/GUIElements.hpp"

#include "irrlicht.h"

#include <iostream>

namespace ic = irr::core;
namespace iv = irr::video;

Scene::Scene()
{
    // display values
    m_wind_speed      = 20;
    m_altitude        = 1000;
    m_vertical_speed  = -20;
    m_gauge_offset    = 0;
    m_stall           = true;

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
    City* airport = new City(m_smgr, "data/airport/airport.obj");
    airport->initialize();
    City* runway = new City(m_smgr, "data/airport/runway.obj");
    runway-> initialize();

    //Init the object plane
    //2 parents: trajectory and rotation
    m_parentNode = m_smgr->addEmptySceneNode();
    m_parentNode->setPosition(ic::vector3df(-662.0, 0.0, -124.0));
    m_parentNode->setRotation(ic::vector3df(0.0, 30.0, 0.0));
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
    manageCollisionsWithSurroundings(airport->getMesh(), airport->getNode());
}

void Scene::initializeGui()
{
    m_device->getFileSystem()->addFileArchive("data.zip");

    // GUI elements mananger
    m_guiManager = new GUIElements();
    m_guiManager->setDevice(m_device);

    // 2D elements initialization
    m_guiManager->initialize2DElements();
}

void Scene::initializeData()
{
    initializeGui();
    initializeObjects();
}

void Scene::manageCollisionsWithSurroundings(irr::scene::IMesh *surroundingMesh, irr::scene::ISceneNode* surroundingNode)
{
    scene::ITriangleSelector *selectorSurrounding;
    selectorSurrounding = m_smgr->createOctreeTriangleSelector(surroundingMesh, surroundingNode);
    surroundingNode->setTriangleSelector(selectorSurrounding);

    m_animCollision = m_smgr->createCollisionResponseAnimator(selectorSurrounding,
                                                 m_parentNode,  //Node
                                                 ic::vector3df(2.8, 0.5, 0.4), // Ellipse dimensions current values ic::vector3df(2.8, 0.5, 0.4)
                                                 ic::vector3df(0, 0.0, 0),       // Gravity
                                                 ic::vector3df(0.0,0.0,0));      // Gap with the center
    m_parentNode->addAnimator(m_animCollision);

    if(m_animCollision->collisionOccurred() == true)
        m_receiver->setIsCrashed(true);

    m_animCollision->drop();
}

void Scene::render()
{
    //Update 2D elements
    std::vector<CGUICompass*> compasses = m_guiManager->update2DElements();

    ic::vector3df firePosition = ic::vector3df(0.0,-0.1,3.);
    m_fire->getPs()->setPosition(m_parentNode->getPosition() + firePosition); //position of the fire particules

    ic::vector3df rotation = m_parentNode->getRotation();
    ic::vector3df position = m_parentNode->getPosition();

    if(m_receiver->getOnFloor())
    {
        m_receiver->planeOnFloor(m_parentRotationNode);

        rotation.Y      = m_receiver->getRotation();
        m_planeSpeed      = m_receiver->getSpeed();
        m_planeAltitude   = m_receiver->getAltitude();

        position.X += m_planeSpeed * sin(rotation.Y * M_PI / 180.0);
        position.Z += m_planeSpeed * cos(rotation.Y * M_PI / 180.0);
        position.Y = m_planeAltitude;

        if (m_planeSpeed > -0.1 && m_planeSpeed < 50)
            m_screw->setRotationStep(10);
        else if (m_planeSpeed > 50)
            m_screw->setRotationStep(30);
        m_screw->updateRotation();
    }
    else if(m_receiver->getInTakeOff())
    {
        m_receiver->planeInTakeOff(m_parentRotationNode, m_leftWing->getNode(), m_rightWing->getNode(),
                                   m_middleTail->getNode(), m_leftTail->getNode(), m_rightTail->getNode());

        m_screw->updateRotation();

        m_planeSpeed      = m_receiver->getSpeed();
        m_planeAltitude   = m_receiver->getAltitude();

        position.X += m_planeSpeed * sin(rotation.Y * M_PI / 180.0);
        position.Z += m_planeSpeed * cos(rotation.Y * M_PI / 180.0);
        position.Y  = m_planeAltitude;
    }
    else if(m_receiver->getInFlight() && !m_receiver->getIsCrashed())
    {
        // Update screw rotation
        m_screw->setRotationStep(30);
        m_screw->updateRotation();

        m_receiver->planeInFlight(m_parentRotationNode, m_leftWing->getNode(), m_rightWing->getNode(),
                                  m_middleTail->getNode(), m_leftTail->getNode(), m_rightTail->getNode());


        rotation.Y      = m_receiver->getRotation();
        m_planeSpeed      = m_receiver->getSpeed();
        m_planeAltitude   = m_receiver->getAltitude();

        position.X += m_planeSpeed * sin(rotation.Y * M_PI / 180.0);
        position.Z += m_planeSpeed * cos(rotation.Y * M_PI / 180.0);
        position.Y  = m_planeAltitude;
    }
    else if(m_receiver->getInLanding())
    {
        m_receiver->planeInLanding(m_parentRotationNode);
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
    }

    std::cout<<"Speed: "<<m_receiver->fromGameUnitToKt(m_planeSpeed)<<" Altitude: "<<m_planeAltitude<<std::endl;

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

