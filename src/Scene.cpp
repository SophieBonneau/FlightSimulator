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
    m_plane = new Plane(m_smgr);

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
    m_camera = m_smgr->addCameraSceneNode(m_plane->getBody()->getNode(), m_cameraPose, m_plane->getParentNode()->getPosition()); //Behind the plane -> (0,5,-34)

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
                                                     m_plane->getParentNode(),  //Node
                                                     ic::vector3df(2.8, 2.0, 0.4), // Ellipse dimensions current values ic::vector3df(2.8, 0.5, 0.4)
                                                     ic::vector3df(0, -1.0, 0),       // Gravity
                                                     ic::vector3df(0.0,0.0,0));      // Gap with the center
    }
    else
    {
        animCollision = m_smgr->createCollisionResponseAnimator(selectorSurrounding,
                                                     m_plane->getParentNode(),  //Node
                                                     ic::vector3df(2.8, 0.5, 0.4), // Ellipse dimensions current values ic::vector3df(2.8, 0.5, 0.4)
                                                     ic::vector3df(0, 0, 0),       // Gravity
                                                     ic::vector3df(0.0,0.0,0));      // Gap with the center
    }
    m_plane->getParentNode()->addAnimator(animCollision);

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
    m_guiManager->setOrientation(m_plane->getParentNode()->getRotation().Y);

    //Update GUI elements
    m_compasses = m_guiManager->update2DElements();
}

void Scene::render()
{
    // GUI update
    updateGui();

    ic::vector3df firePosition = ic::vector3df(0.0,-0.1,3.);
    m_fire->getPs()->setPosition(m_plane->getParentNode()->getPosition() + firePosition); //position of the fire particules

    ic::vector3df rotation = m_plane->getParentNode()->getRotation();

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
            core::vector3df rotation = m_plane->getScrew()->getNode()->getRotation();
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
        firePosition = m_plane->getParentNode()->getPosition();
        m_fire->getPs()->setEmitter(m_fire->getEm());
    }
    else if(m_receiver->getOnFloor())
    {
        m_receiver->planeOnFloor(m_plane->getParentRotationNode());

        // Update plane rotation
        rotation.Y      = m_receiver->getRotation();

        m_plane->setPlaneSpeed(m_receiver->getSpeed());
        m_plane->setPlaneAltitude(m_receiver->getAltitude());

        if (m_plane->getPlaneSpeed() > -0.1 && m_plane->getPlaneSpeed() < 50)
            m_plane->getScrew()->setRotationStep(10);
        else if (m_plane->getPlaneSpeed() > 50)
            m_plane->getScrew()->setRotationStep(30);
        m_plane->getScrew()->updateRotation();
    }
    else if(m_receiver->getInTakeOff())
    {
        m_receiver->planeInTakeOff(m_plane->getParentRotationNode(), m_plane->getLeftWing()->getNode(), m_plane->getRightWing()->getNode(),
                                   m_plane->getMiddleTail()->getNode(), m_plane->getLeftTail()->getNode(), m_plane->getRightTail()->getNode());

        m_plane->getScrew()->updateRotation();

        m_plane->setPlaneSpeed(m_receiver->getSpeed());
        m_plane->setPlaneAltitude(m_receiver->getAltitude());
    }
    else if(m_receiver->getInFlight())
    {
        m_receiver->planeInFlight(m_plane->getParentRotationNode(), m_plane->getLeftWing()->getNode(), m_plane->getRightWing()->getNode(),
                                  m_plane->getMiddleTail()->getNode(), m_plane->getLeftTail()->getNode(), m_plane->getRightTail()->getNode());

        // Update screw rotation
        m_plane->getScrew()->setRotationStep(30);
        m_plane->getScrew()->updateRotation();

        // Update plane rotation
        rotation.Y      = m_receiver->getRotation();

        m_plane->setPlaneSpeed(m_receiver->getSpeed());
        m_plane->setPlaneAltitude(m_receiver->getAltitude());
    }
    else if(m_receiver->getInLanding())
    {
        std::cout<<"In landing"<<std::endl;
        m_receiver->planeInLanding(m_plane->getParentRotationNode(), m_plane->getLeftTail()->getNode(), m_plane->getRightTail()->getNode());
    }

    // Update the plane position
    m_plane->computeNewPosition(rotation);

    //Camera pose
    m_receiver->changeCameraPose(m_camera);
    if(m_camera->getPosition().Z < -10.0)
    {
        m_plane->getBody()->getNode()->setVisible(true);
        m_plane->getScrew()->getNode()->setVisible(true);
        m_camera->setParent(m_plane->getBody()->getNode());
        m_camera->setTarget(m_plane->getParentNode()->getPosition());

        // Update screw rotation
        m_plane->getScrew()->updateRotation();
    }
    else
    {
        m_camera->setParent(m_plane->getParentRotationNode());
        m_camera->setTarget(m_plane->getParentNode()->getPosition());
        m_plane->getBody()->getNode()->setVisible(false);
        m_plane->getScrew()->getNode()->setVisible(false);
    }

    //Back color
    m_driver->beginScene(true,true,iv::SColor(100,150,200,255));

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


