#include "Scene.hpp"

#include "GUI/GUIElements.hpp"

#include "irrlicht.h"

#include <iostream>

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Scene::Scene()
{
    // display values
    this->wind_speed      = 20;
    this->altitude        = 1000;
    this->vertical_speed  = -20;
    this->gauge_offset    = 0;
    this->stall          = true;

    this->planeSpeed    = 0.0f;
    this->planeAltitude = 0.0f;
    this->rotAngle      = 0.0f;
}

void Scene::initializeIrrlicht()
{
    // Event manager
    this->receiver = new EventReceiver();

    // Window and rendering system creation
    this->device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d<u32>(640, 480),
                                          16, false, false, false, receiver);
    this->driver = device->getVideoDriver();
    this->smgr  = device->getSceneManager();
    this->gui = device->getGUIEnvironment();
}

void Scene::manageCollisionsWithSurroundings(is::ISceneManager *smgr,
                                 is::IMesh *city_mesh,
                                 is::ISceneNode* city_node,
                                 is::IMeshSceneNode *plane,
                                 is::ISceneNode *parentNode)
{
    // Création du triangle selector
    scene::ITriangleSelector *selector_city;
    selector_city = smgr->createOctreeTriangleSelector(city_mesh, city_node);
    city_node->setTriangleSelector(selector_city);
    // Et l'animateur/collisionneur
    scene::ISceneNodeAnimator *anim_collision_plane_city;
    anim_collision_plane_city = smgr->createCollisionResponseAnimator(selector_city,
                                                 parentNode,  // Le noeud que l'on veut gérer
                                                 ic::vector3df(2.8, 0.5, 0.4), // "rayons" du perso
                                                 ic::vector3df(0, 0, 0),  // gravity
                                                 ic::vector3df(1.0,0,0));  //décalage du centre
    parentNode->addAnimator(anim_collision_plane_city);
    //smgr->addSphereSceneNode(5.0,16,0,-1,ic::vector3df(10,0,0),ic::vector3df(0,0,0),ic::vector3df(1.0,1.0,1.0));
}

void Scene::initializeData()
{
    // GUI elements mananger
    this->guiManager = new GUIElements();
    guiManager->setDevice(device);

    device->getFileSystem()->addFileArchive("data.zip");

    //City
    City* city = new City(smgr, "data/city/city_cercles.obj");
    city->initialize();

    //Init the object plane
    //2 parents: trajectory and rotation
    this->parentNode = smgr->addEmptySceneNode();
    this->parentRotationNode = smgr->addEmptySceneNode();
    parentRotationNode->setParent(parentNode);

    //Init the plane
    this->body = new Body(smgr, parentRotationNode, "data/plane/plane.obj");
    body->initialize();

    //Init the screw
    this->screw = new Screw(smgr, parentRotationNode, "data/plane/screw.obj");
    screw->initialize();

    //Init the two wings
    this->leftWing = new Wing(smgr, parentRotationNode,"data/plane/leftWing.obj");
    leftWing->setPosition(ic::vector3df(-0.667,0.303,0.19));
    leftWing->initialize();
    this->rightWing = new Wing(smgr, parentRotationNode,"data/plane/rightWing.obj");
    rightWing->setPosition(ic::vector3df(0.667,0.303,0.19));
    rightWing->initialize();

    //Init the three tails
    this->middleTail = new Tail(smgr, parentRotationNode, "data/plane/tail.obj");
    middleTail->setPosition(ic::vector3df(0.001,0.355,-0.53));
    middleTail->initialize();
    this->leftTail = new Tail(smgr, parentRotationNode, "data/plane/leftTail.obj");
    leftTail->setPosition(ic::vector3df(-0.205,0.23,-0.441));
    leftTail->initialize();
    this->rightTail = new Tail(smgr, parentRotationNode, "data/plane/rightTail.obj");
    rightTail->setPosition(ic::vector3df(0.208,0.225,-0.441));
    rightTail->initialize();

    //Water
    Water* water = new Water(smgr, driver->getTexture("data/water/water.jpg"));
    water->initialize();

    // 2D elements initialization
    guiManager->initialize2DElements();

    // Collision management with surroundings
    manageCollisionsWithSurroundings(smgr, city->getMesh(), city->getNode(), body->getNode(), parentNode);
}

void Scene::render()
{
    //Update 2D elements
    std::vector<CGUICompass*> compasses = guiManager->update2DElements();

    //If the plane is flying then
    //  inFlight = true
    //Else, ie. plane on the ground, in take-off position and in landing position
    //  inFlight = false
    ic::vector3df rotation = parentNode->getRotation();
    ic::vector3df position = parentNode->getPosition();

    if(receiver->getOnFloor())
    {
        receiver->planeOnFloor(parentRotationNode);

        rotation.Y      = receiver->getRotation();
        planeSpeed      = receiver->getSpeed();

        position.X += planeSpeed * sin(rotation.Y * M_PI / 180.0);
        position.Z += planeSpeed * cos(rotation.Y * M_PI / 180.0);
    }
    else if(receiver->getInTakeOff())
    {
        std::cout<<"TD : plane is taking off"<<std::endl;
    }
    else if(receiver->getInFlight())
    {
        // Update screw rotation
        screw->updateRotation();

        //receiver.planeInFlight(parentRotationNode, leftwing_node, rightwing_node, tail_node, lefttail_node, rightttail_node);

        receiver->planeInFlight(parentRotationNode, leftWing->getNode(), rightWing->getNode(), middleTail->getNode(), leftTail->getNode(), rightTail->getNode());


        rotation.Y      = receiver->getRotation();
        planeSpeed      = receiver->getSpeed();
        planeAltitude   = receiver->getAltitude();

        position.X += planeSpeed * sin(rotation.Y * M_PI / 180.0);
        position.Z += planeSpeed * cos(rotation.Y * M_PI / 180.0);
        position.Y  = planeAltitude;
    }
    else if(receiver->getInLanding())
    {
        std::cout<<"TD : plane is landing"<<std::endl;
    }
    else if(receiver->getIsStalling())
    {
        std::cout<<"TD : the plane is stalling"<<std::endl;
    }
    else
    {
        std::cout<<"TD : the plane has crashed"<<std::endl;
    }

    parentNode->setRotation(rotation);
    parentNode->setPosition(position);

    //Camera position
    smgr->addCameraSceneNode(body->getNode(), ic::vector3df(0, 5, -34), parentNode->getPosition()); //0,5,-34

    //Back color
    driver->beginScene(true,true,iv::SColor(100,150,200,255));

    // Draw the scene
    smgr->drawAll();
    gui->drawAll();

    for(unsigned int i = 0; i < compasses.size(); i++)
    {
        compasses[i]->draw();
    }

    driver->endScene();
}


