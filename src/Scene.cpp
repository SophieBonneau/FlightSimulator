#include "Scene.hpp"

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

    m_cameraPose = ic::vector3df(0.0,5.0,-34.0);
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
    Landscape* city = new Landscape(m_smgr, "data/city/city_cercles.obj");
    city->initialize();
    Landscape* airport = new Landscape(m_smgr, "data/airport/buildings.obj");
    airport->initialize();
    Landscape* runway = new Landscape(m_smgr, "data/airport/runway.obj");
    runway-> initialize();
    Landscape* runway2 = new Landscape(m_smgr, "data/airport/runway2.obj");
    runway2-> initialize();

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
    m_screw->setPosition(ic::vector3df(0.0,0.19,0.58));
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
    m_water = new Water(m_smgr, m_driver->getTexture("data/water/water.jpg"), m_driver->getTexture("data/water/waterPool.jpg"));
    m_water->initialize();

    //Fire
    m_fire = new Fire(m_smgr, m_driver->getTexture("data/fire/fire.jpg"));
    m_fire->initialize();

    //Sky
    m_smgr->addSkyDomeSceneNode(m_driver->getTexture("data/sky/sky.jpg"),16,8,0.95f,2.0f);
    m_driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

    //Camera position
    m_camera = m_smgr->addCameraSceneNode(m_body->getNode(), m_cameraPose, m_parentNode->getPosition()); //Behind the plane -> (0,5,-34)

    // Collision management with surroundings
    m_animCollisionAirport  = manageCollisionsWithSurroundings(airport, false);
    m_animCollisionCity     = manageCollisionsWithSurroundings(city, false);
    m_animCollisionRunway   = manageCollisionsWithSurroundings(runway, false);
    m_animCollisionRunway2  = manageCollisionsWithSurroundings(runway2, false);
}

void Scene::initializeGui()
{
    m_device->getFileSystem()->addFileArchive("data.zip");

    // GUI elements mananger
    m_guiManager = new GUIElements(m_device);

    // 2D elements initialization
    m_guiManager->initialize2DElements();
}

void Scene::initializeData()
{
    initializeGui();
    initializeObjects();
}

is::ISceneNodeAnimatorCollisionResponse* Scene::manageCollisionsWithSurroundings(Landscape* building, bool gravity)
{
    // Collision management with surroundings
    is::ITriangleSelector *selectorSurrounding;
    selectorSurrounding = m_smgr->createOctreeTriangleSelector(building->getMesh(), building->getNode());
    building->getNode()->setTriangleSelector(selectorSurrounding);

    is::ISceneNodeAnimatorCollisionResponse* animCollision;
    if(gravity)
    {
        animCollision = m_smgr->createCollisionResponseAnimator(selectorSurrounding,
                                                     m_parentNode,  //Node
                                                     ic::vector3df(2.8, 2.0, 0.4), // Ellipse dimensions current values ic::vector3df(2.8, 0.5, 0.4)
                                                     ic::vector3df(0, -1.0, 0),       // Gravity
                                                     ic::vector3df(0.0,0.0,0));      // Gap with the center
    }
    else
    {
        animCollision = m_smgr->createCollisionResponseAnimator(selectorSurrounding,
                                                     m_parentNode,  //Node
                                                     ic::vector3df(2.8, 0.5, 0.4), // Ellipse dimensions current values ic::vector3df(2.8, 0.5, 0.4)
                                                     ic::vector3df(0, 0, 0),       // Gravity
                                                     ic::vector3df(0.0,0.0,0));      // Gap with the center
    }
    m_parentNode->addAnimator(animCollision);

    return animCollision;
}

void Scene::updateGui()
{
    // Link simulation values to GUI
    m_guiManager->setAltitude(m_receiver->getAltitudeM());
    m_guiManager->setAlmostStall(m_receiver->getIsAlmostStalling());
    m_guiManager->setStall(m_receiver->getIsStalling());
    m_guiManager->setGaugeHPercentage(m_receiver->getFuelLiter());
    m_guiManager->setGaugeVSlope(m_receiver->getSlopePercent());
    m_guiManager->setSpeed(m_receiver->getSpeedKmH());
    m_guiManager->setVerticalSpeed(m_receiver->getAltitudeSpeed());
    m_guiManager->setOrientation(m_parentNode->getRotation().Y);

    //Update GUI elements
    m_compasses = m_guiManager->update2DElements();
}

void Scene::render()
{
    // GUI update
    updateGui();

    ic::vector3df firePosition = ic::vector3df(0.0,-0.1,3.);
    m_fire->getPs()->setPosition(m_parentNode->getPosition() + firePosition); //position of the fire particules

    ic::vector3df rotation = m_parentNode->getRotation();
    ic::vector3df position = m_parentNode->getPosition();

    if(m_animCollisionAirport->collisionOccurred())
    {
        m_receiver->setIsCrashed(true);
        m_animCollision = m_animCollisionAirport;
    }
    else if(m_animCollisionCity->collisionOccurred())
    {
        m_receiver->setIsCrashed(true);
        m_animCollision = m_animCollisionCity;
    }
    else if(m_animCollisionRunway2->collisionOccurred())
    {
        if(m_receiver->getInFlight())
        {
            core::vector3df rotation = m_screw->getNode()->getRotation();
            std::cout<<"rotation.X "<<rotation.X<<std::endl;
            if(rotation.X < 3.0)
                m_receiver->setIsLanding(true);
        }
        else if (!m_receiver->getOnFloor())
        {
            m_receiver->setIsCrashed(true);
            m_animCollision = m_animCollisionCity;
        }
    }
    if(m_receiver->getIsCrashed() && m_animCollisionCity->collisionOccurred())
    {
        firePosition.X = m_animCollision->getCollisionPoint().X;
        firePosition.Y = m_animCollision->getCollisionPoint().Y;
        firePosition.Z = m_animCollision->getCollisionPoint().Z;
        m_fire->getPs()->setEmitter(m_fire->getEm()); // this grabs the emitter of fire particules
    }
    else if(m_receiver->getIsCrashed())
    {
        firePosition = m_parentNode->getPosition();
        m_fire->getPs()->setEmitter(m_fire->getEm());
    }
    else if(m_receiver->getOnFloor())
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
    else if(m_receiver->getInFlight())
    {
        m_receiver->planeInFlight(m_parentRotationNode, m_leftWing->getNode(), m_rightWing->getNode(),
                                  m_middleTail->getNode(), m_leftTail->getNode(), m_rightTail->getNode());

        // Update screw rotation
        m_screw->setRotationStep(30);
        m_screw->updateRotation();

        rotation.Y      = m_receiver->getRotation();
        m_planeSpeed      = m_receiver->getSpeed();
        m_planeAltitude   = m_receiver->getAltitude();

        position.X += m_planeSpeed * sin(rotation.Y * M_PI / 180.0);
        position.Z += m_planeSpeed * cos(rotation.Y * M_PI / 180.0);
        position.Y  = m_planeAltitude;
    }
    else if(m_receiver->getInLanding())
    {
        std::cout<<"In landing"<<std::endl;
        m_receiver->planeInLanding(m_parentRotationNode, m_leftTail->getNode(), m_rightTail->getNode());
    }

    m_parentNode->setRotation(rotation);
    m_parentNode->setPosition(position);

    //Camera pose
    m_receiver->changeCameraPose(m_camera);
    if(m_camera->getPosition().Z < -10.0)
    {
        m_body->getNode()->setVisible(true);
        m_screw->getNode()->setVisible(true);
        m_camera->setParent(m_body->getNode());
        m_camera->setTarget(m_parentNode->getPosition());

        // Update screw rotation
        m_screw->updateRotation();
    }
    else
    {
        m_camera->setParent(m_parentRotationNode);
        m_camera->setTarget(m_parentNode->getPosition());
        m_body->getNode()->setVisible(false);
        m_screw->getNode()->setVisible(false);
    }

    //Back color
    m_driver->beginScene(true,true,iv::SColor(100,150,200,255));
    //_driver->

    // Draw the scene
    m_smgr->drawAll();
    m_gui->drawAll();

    // Draw GUI compasses
    for(unsigned int i = 0; i < m_compasses.size(); i++)
    {
         m_compasses[i]->draw();
    }

    m_driver->endScene();
}


