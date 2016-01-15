#include <irrlicht.h>
#include <iostream>
#include <time.h>
#include <vector>

#include "CGUICompass.hpp"
#include "GUIElements.hpp"

using namespace irr;
namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


struct MyEventReceiver : IEventReceiver
{
    is::ISceneNode *node;
    is::ISceneNode *parentNode;
    is::IAnimatedMeshSceneNode *leftwing_node;
    bool keyIsDown[KEY_KEY_CODES_COUNT];

    //Init steps
    const float speedStep         = 0.005f;
    const float altitudeAngleStep = 0.1;
    const float rotationAngleStep = 0.1f;

    //Init plane constructor parameters
    const float voidPlaneWeightKg = 957.0f;

    const float minPlaneSpeedKt  = 0.0f;
    const float maxPlaneSpeedKt  = 158.0f;
    const float flatStallSpeedKt = 44.0f;

    const float minPlaneSpeed   = fromKtToGameUnit(minPlaneSpeedKt);
    const float maxPlaneSpeed   = fromKtToGameUnit(maxPlaneSpeedKt);
    const float flatStallSpeed  = fromKtToGameUnit(flatStallSpeedKt);

    //Init plane limits values
    float loadFactor = 1.0f;
    float stallSpeed = -100.0f;

    //Init moving plane values
    float planeWeight     = voidPlaneWeightKg;
    float planeSpeed      = 0.0f;
    float planeSpeedFloor = 0.0f;
    float planeAltitude   = 0.0f;
    float rotationAngle   = 0.0f;

    /************************************************************************************/
    /******************************** Constructor ***************************************/
    /************************************************************************************/
    MyEventReceiver()
    {
        for(unsigned int i = 0; i<KEY_KEY_CODES_COUNT; ++i)
            keyIsDown[i] = false;
    }

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* float getSpeed: getter for the speed value
     * return:  planeSpeed: the speed value
    */
    float getAltitude(){    return planeAltitude;  }

    /* float getAltitude: getter for the altitude value
     * return:  planeAltitude: the altitude value
    */
    float getSpeed(){    return planeSpeedFloor;  }

    /* float getRotation: getter for the rotation value (plane go to the left or the right)
     * return:  rotationAngle: the rotation value
    */
    float getRotation(){    return rotationAngle;  }

    /* void setPlaneWeight: function used to initialize the planeWeight
     * params:  const float planeWeight:      the plane weight
    */
    void setPlaneWeight(const float planeWeight){     this->planeWeight = planeWeight;    }

    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/
    float fromKtToGameUnit(float valueToConvert)
    {
        return valueToConvert / 300.0f;
    }

    float fromGameUnitToKt(float valueToConvert)
    {
        return valueToConvert * 300.0f;
    }

    void movePlane(is::ISceneNode *node,
                   is::IAnimatedMeshSceneNode *leftwing_node, is::IAnimatedMeshSceneNode *rightwing_node,
                   is::IAnimatedMeshSceneNode *tail_node,
                   is::IAnimatedMeshSceneNode *lefttail_node, is::IAnimatedMeshSceneNode *righttail_node)
    {
        if(stallSpeed < planeSpeed && stallSpeed * 1.1 > planeSpeed)
        {
        }
        if(stallSpeed >= planeSpeed)
        {
        }
        //Increase or decrease the plane speed
        ic::vector3df childRotation = node->getRotation();
        ic::vector3df leftwingRotation = leftwing_node->getRotation();
        ic::vector3df rightwingRotation = rightwing_node->getRotation();
        ic::vector3df tailRotation = tail_node->getRotation();
        ic::vector3df lefttailRotation = lefttail_node->getRotation();
        ic::vector3df righttailRotation = righttail_node->getRotation();

        if(keyIsDown[KEY_KEY_Z] == true)
        {
            if(planeSpeed < maxPlaneSpeed)
            {
                planeSpeed += speedStep;
                planeSpeedFloor = planeSpeed;
            }
        }
        if(keyIsDown[KEY_KEY_S] == true)
        {
            if(planeSpeed > minPlaneSpeed)
            {
                planeSpeed -= speedStep;
                planeSpeedFloor = planeSpeed;
            }
        }

        //Open the side panels of the plane to turn to the right or the left
        if(keyIsDown[KEY_KEY_D] == true)

        {
            //TD: Add the wind effect
            //If the plane is flat (not in the wrong inclinaison)
            if(childRotation.Z <= 0)
            {
                childRotation.Z -= rotationAngleStep;
                leftwingRotation.X -= 0.1;
                rightwingRotation.X += 0.1;
                tailRotation.Y -= 0.1;
                tailRotation.Z += 0.05;
            }
            else
            {
                childRotation.Z -= 2 * rotationAngleStep;
                leftwingRotation.X -= 2 * 0.1;
                rightwingRotation.X += 2 * 0.1;
                tailRotation.Y -= 2 * 0.1;
                tailRotation.Z += 2 * 0.05;
            }
        }
        if(keyIsDown[KEY_KEY_Q] == true)
        {
            if(childRotation.Z >= 0)
            {
                childRotation.Z += rotationAngleStep;
                leftwingRotation.X += 0.1;
                rightwingRotation.X -= 0.1;
                tailRotation.Y += 0.1;
                tailRotation.Z -= 0.05;
            }
            else
            {
                childRotation.Z += 2 * rotationAngleStep;
                leftwingRotation.X += 2 * 0.1;
                rightwingRotation.X -= 2* 0.1;
                tailRotation.Y += 2 * 0.1;
                tailRotation.Z -= 2 * 0.05;
            }
        }
        //Get the plane up or down
        if(keyIsDown[KEY_KEY_A] == true)
        {
            childRotation.X -= altitudeAngleStep;
            lefttailRotation.X += 0.1;
            righttailRotation.X += 0.1;
        }
        if(keyIsDown[KEY_KEY_E] == true)
        {
            childRotation.X += altitudeAngleStep;
            lefttailRotation.X -= 0.1;
            righttailRotation.X -= 0.1;

        }

        node->setRotation(childRotation);
        leftwing_node->setRotation(leftwingRotation);
        rightwing_node->setRotation(rightwingRotation);
        tail_node->setRotation(tailRotation);
        lefttail_node->setRotation(lefttailRotation);
        righttail_node->setRotation(righttailRotation);

        planeSpeedFloor = cos(childRotation.X * core::DEGTORAD) * planeSpeed;
        planeAltitude -= sin(childRotation.X * core::DEGTORAD) * planeSpeed;

        //std::cout<<"Altitude virage : "<<planeAltitude<<std::endl;

        rotationAngle -= childRotation.Z / 20;

        //Compute the stall speed
        loadFactor = (1/cos(-childRotation.Z*core::DEGTORAD));
        stallSpeed = sqrt(loadFactor) * flatStallSpeed;
    }

    /************************************************************************************/
    /******************************** Events ********************************************/
    /************************************************************************************/
    bool OnEvent(const SEvent &event)
    {
        // Si l'événement est de type clavier (KEY_INPUT)
        // et du genre pressage de touche
        // et que la touche est escape, on sort du programme
        if (event.EventType == EET_KEY_INPUT_EVENT)
        {
            if(event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.Key == KEY_ESCAPE)
            {
                exit(0);
            }
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Z && !keyIsDown[KEY_KEY_Z]) // Avance
            {
                keyIsDown[KEY_KEY_Z] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Z && keyIsDown[KEY_KEY_Z]) // Stop Avance
            {
                keyIsDown[KEY_KEY_Z] = false;
            }
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_S && !keyIsDown[KEY_KEY_S]) // Go back
            {
                keyIsDown[KEY_KEY_S] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_S) // Stop going back
            {
                keyIsDown[KEY_KEY_S] = false;
            }
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Q && !keyIsDown[KEY_KEY_Q]) // Go left
            {
                keyIsDown[KEY_KEY_Q] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Q) // Stop going left
            {
                keyIsDown[KEY_KEY_Q] = false;
            }
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_D && !keyIsDown[KEY_KEY_D]) // Go right
            {
                keyIsDown[KEY_KEY_D] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_D) // Stop going right
            {
                keyIsDown[KEY_KEY_D] = false;
            }
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_A && !keyIsDown[KEY_KEY_A]) // Go up
            {
                keyIsDown[KEY_KEY_A] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_A) // Stop going up
            {
                keyIsDown[KEY_KEY_A] = false;
            }
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_E && !keyIsDown[KEY_KEY_E]) // Go down
            {
                keyIsDown[KEY_KEY_E] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_E) // Stop going down
            {
                keyIsDown[KEY_KEY_E] = false;
            }
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_P && !keyIsDown[KEY_KEY_P]) // Go rearing plane
            {
                keyIsDown[KEY_KEY_P] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_P) // Stop going rearing
            {
                keyIsDown[KEY_KEY_P] = false;
            }
        }

        return false;
    }
};

is::ISceneNodeAnimatorCollisionResponse* manageCollisionsWithScenery(is::ISceneManager *smgr,
                                 is::IMesh *landscape_mesh,
                                 is::ISceneNode* landscape_node,
                                 is::ISceneNode *plane_node)
{
    //Collision with the landscape
    scene::ITriangleSelector *selector_landscape;
    selector_landscape = smgr->createOctreeTriangleSelector(landscape_mesh, landscape_node);
    landscape_node->setTriangleSelector(selector_landscape);
    selector_landscape->drop();
    // Et l'animateur/collisionneur
    scene::ISceneNodeAnimatorCollisionResponse *anim_collision_plane_landscape;
    anim_collision_plane_landscape = smgr->createCollisionResponseAnimator(selector_landscape,
                                                 plane_node,  // Le noeud que l'on veut gérer
                                                 ic::vector3df(2.8, 0.5, 0.4), // "rayons" du perso
                                                 ic::vector3df(0, 0, 0),  // gravity
                                                 ic::vector3df(0, 0, 0));  //décalage du centre
    plane_node->addAnimator(anim_collision_plane_landscape);
    anim_collision_plane_landscape->drop();

    return anim_collision_plane_landscape;
}

int main()
{
    // display values
    int wind_speed      = 20;
    int altitude        = 1000;
    int vertical_speed  = -20;
    int gauge_offset    = 0;
    bool stall          = true;

    // Event manager
    MyEventReceiver receiver;

    // Window and rendering system creation
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d<u32>(640, 480),
                                          16, false, false, false, &receiver);
    iv::IVideoDriver *driver = device->getVideoDriver();
    is::ISceneManager *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui = device->getGUIEnvironment();

    // GUI elements mananger
    GUIElements* guiManager = new GUIElements();
    guiManager->setDevice(device);

    device->getFileSystem()->addFileArchive("data.zip");

    //Landscape and cities
    is::IMesh *cityMesh = smgr->getMesh("data/city/city_cercles.obj");
    is::ISceneNode *cityNode;
    cityNode = smgr->addOctreeSceneNode(cityMesh,nullptr,-1,1024);
    cityNode->setMaterialFlag(iv::EMF_LIGHTING,false);
    cityNode->setScale(ic::vector3df(10,10,10));

    //Airport and runway
    is::IMesh *airportMesh = smgr->getMesh("data/airport/airport.obj");
    is::ISceneNode *airportNode;
    airportNode = smgr->addOctreeSceneNode(airportMesh,nullptr,-1,1024);
    airportNode->setMaterialFlag(iv::EMF_LIGHTING,false);
    airportNode->setScale(ic::vector3df(10,10,10));
    is::IMesh *runway_mesh = smgr->getMesh("data/airport/runway.obj");
    is::ISceneNode *runway_node;
    runway_node = smgr->addOctreeSceneNode(runway_mesh,nullptr,-1,1024);
    runway_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    runway_node->setScale(ic::vector3df(10,10,10));

    //Init the object plane
    //2 parents: trajectory and rotation
    is::ISceneNode *parentNode = smgr->addEmptySceneNode();
    is::ISceneNode *parentRotationNode = smgr->addEmptySceneNode();
    parentRotationNode->setParent(parentNode);

    //Init the plane
    is::IAnimatedMesh *plane_mesh = smgr->getMesh("data/plane/plane.obj");
    is::IAnimatedMeshSceneNode *plane_node= smgr->addAnimatedMeshSceneNode(plane_mesh);
    plane_node->setParent(parentRotationNode);
    plane_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    plane_node->setScale(ic::vector3df(0.05,0.05,0.05));

    //Init the screw
    is::IAnimatedMesh *screw_mesh = smgr->getMesh("data/plane/screw.obj");
    is::IAnimatedMeshSceneNode *screw_node= smgr->addAnimatedMeshSceneNode(screw_mesh);
    screw_node->setParent(parentRotationNode);
    screw_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    screw_node->setScale(ic::vector3df(0.05,0.05,0.05));
    screw_node->setPosition(ic::vector3df(0.0,0.19,0.58));

    //Init the two wings
    is::IAnimatedMesh *leftwing_mesh = smgr->getMesh("data/plane/leftWing.obj");
    is::IAnimatedMesh *rightwing_mesh = smgr->getMesh("data/plane/rightWing.obj");
    is::IAnimatedMeshSceneNode *leftwing_node = smgr->addAnimatedMeshSceneNode(leftwing_mesh);
    is::IAnimatedMeshSceneNode *rightwing_node = smgr->addAnimatedMeshSceneNode(rightwing_mesh);
    leftwing_node->setParent(parentRotationNode);
    leftwing_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    leftwing_node->setScale(ic::vector3df(0.05,0.05,0.05));
    leftwing_node->setPosition(ic::vector3df(-0.667,0.303,0.19));
    rightwing_node->setParent(parentRotationNode);
    rightwing_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    rightwing_node->setScale(ic::vector3df(0.05,0.05,0.05));
    rightwing_node->setPosition(ic::vector3df(0.667,0.306,0.19));

    //Init the tail
    is::IAnimatedMesh *tail_mesh = smgr->getMesh("data/plane/tail.obj");
    is::IAnimatedMeshSceneNode *tail_node= smgr->addAnimatedMeshSceneNode(tail_mesh);
    tail_node->setParent(parentRotationNode);
    tail_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    tail_node->setScale(ic::vector3df(0.05,0.05,0.05));
    tail_node->setPosition(ic::vector3df(0.001,0.355,-0.53));

    //Init the left and right tails
    is::IAnimatedMesh *lefttail_mesh = smgr->getMesh("data/plane/leftTail.obj");
    is::IAnimatedMeshSceneNode *lefttail_node= smgr->addAnimatedMeshSceneNode(lefttail_mesh);
    lefttail_node->setParent(parentRotationNode);
    lefttail_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    lefttail_node->setScale(ic::vector3df(0.05,0.05,0.05));
    lefttail_node->setPosition(ic::vector3df(-0.205,0.23,-0.441));
    is::IAnimatedMesh *rightttail_mesh = smgr->getMesh("data/plane/rightTail.obj");
    is::IAnimatedMeshSceneNode *rightttail_node= smgr->addAnimatedMeshSceneNode(rightttail_mesh);
    rightttail_node->setParent(parentRotationNode);
    rightttail_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    rightttail_node->setScale(ic::vector3df(0.05,0.05,0.05));
    rightttail_node->setPosition(ic::vector3df(0.208,0.225,-0.441));

    //Water
     is::IMesh *mesh_water = smgr->addHillPlaneMesh( "myHill",
           core::dimension2d<f32>(4.6,4.6),
           core::dimension2d<u32>(200,200), 0, 0,
           core::dimension2d<f32>(0,0),
           core::dimension2d<f32>(5,5));
    scene::ISceneNode* plan_water = smgr->addWaterSurfaceSceneNode(mesh_water, 0.2f, 500.0f, 10.0f);
    plan_water->setMaterialTexture(0, driver->getTexture("data/water/water.jpg"));
    plan_water->setMaterialFlag(iv::EMF_LIGHTING, false);
    plan_water->setMaterialType(video::EMT_REFLECTION_2_LAYER);
    plan_water->setPosition(ic::vector3df(0,-2, 0));

    //Fire
    // create a particle system
    scene::IParticleSystemSceneNode* ps = smgr->addParticleSystemSceneNode(false);
    scene::IParticleEmitter* em = ps->createBoxEmitter(
        core::aabbox3d<f32>(-7,0,-7,7,1,7), // emitter size
        core::vector3df(0.0f,0.0f,0.0f),   // initial direction
        800,1000,                             // emit rate
        video::SColor(0,255,0,0),       // darkest color
        video::SColor(0,255,200,200),       // brightest color
        500,800,0,                         // min and max age, angle
        core::dimension2df(1.f,1.f),         // min size
        core::dimension2df(2.f,2.f));        // max size

    scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
    ps->addAffector(paf); // same goes for the affector
    paf->drop();
    ps->setScale(core::vector3df(0.5,0.5,0.5));
    ps->setMaterialFlag(video::EMF_LIGHTING, false);
    ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    ps->setMaterialTexture(0, driver->getTexture("data/fire/fire.jpg"));
    ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

    // 2D elements initialization
    guiManager->initialize2DElements();

    // Collision management with scenery
    scene::ISceneNodeAnimatorCollisionResponse *collisionCity;
    scene::ISceneNodeAnimatorCollisionResponse *collisionAirport;
    collisionCity = manageCollisionsWithScenery(smgr, cityMesh, cityNode, parentNode);
    collisionAirport = manageCollisionsWithScenery(smgr, airportMesh, airportNode, parentNode);

    //Init the plane state
    //To change to false: true only for tests
    bool inFlight = true;

    float planeWeigth = 1000.0f;
    receiver.setPlaneWeight(planeWeigth);

    float planeSpeed    = 0.0f;
    float planeAltitude = 0.0f;
    float rotAngle      = 0.0f;

    bool crash = false;

    while(device->run())
    {
        //Update 2D elements
        std::vector<CGUICompass*> compasses = guiManager->update2DElements();

        //If the plane is flying then
        //  inFlight = true
        //Else, ie. plane on the ground, in take-off position and in landing position
        //  inFlight = false

        ic::vector3df rotation_screw = screw_node->getRotation();

        if(inFlight && crash == false)
        {
            //Movements of the plane
            ic::vector3df rotation = parentNode->getRotation();

            rotation.Y = receiver.getRotation();
            parentNode->setRotation(rotation);

            planeSpeed      = receiver.getSpeed();
            planeAltitude   = receiver.getAltitude();

            ic::vector3df position = parentNode->getPosition();

            position.X += planeSpeed * sin(rotation.Y * M_PI / 180.0);
            position.Z += planeSpeed * cos(rotation.Y * M_PI / 180.0);
            position.Y  = planeAltitude;

            rotation_screw.Z += 30.0;

            parentNode->setPosition(position);
            screw_node->setRotation(rotation_screw);

            receiver.movePlane(parentRotationNode, leftwing_node, rightwing_node, tail_node, lefttail_node, rightttail_node);

        }
        else
        {
            std::cout<<"TD : plane on the ground, in take-off position and in landing position"<<std::endl;
        }

        //Detection of collisions
        ic::vector3df firePosition = ic::vector3df(0.0,-0.1,3.);
        ps->setPosition(parentNode->getPosition() + firePosition); //position of the fire particules
        if(collisionCity->collisionOccurred() == true)
        {
            firePosition.X = collisionCity->getCollisionPoint().X;
            firePosition.Y = collisionCity->getCollisionPoint().Y;
            firePosition.Z = collisionCity->getCollisionPoint().Z;
            ps->setEmitter(em); // this grabs the emitter of fire particules

            crash = true;
        }

        //Camera position
        smgr->addCameraSceneNode(plane_node, ic::vector3df(0, 5, -34), parentNode->getPosition()); //0,5,-34

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
    device->drop();
    return 0;

}
