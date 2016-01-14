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
    bool keyIsDown[KEY_KEY_CODES_COUNT];

    //Init steps
    const float speedStep         = 0.005f;
    const float motorStep         = 0.01f;
    const float altitudeAngleStep = 0.1;
    const float rotationAngleStep = 0.1f;

    //Init plane constructor parameters
    const float voidPlaneWeightKg = 957.0f;     //Fuel included
    const float g = 9.81f;  //m.s-2

    //const float bearing = ; // Portance ???
    const float wingLoading = 68.84f; //Charge alaire kg.m-2

    const float minPlaneSpeedKt  = 0.0f;    //Kt
    const float maxPlaneSpeedKt  = 158.0f;  //Kt
    const float flatStallSpeedKt = 44.0f;   //Kt

    //Init motor const
    float const minMotorPower = 0.0f;
    float const maxMotorPower = 16.0f;

    const float minPlaneSpeed   = fromKtToGameUnit(minPlaneSpeedKt);    //Irrlicht unit
    const float maxPlaneSpeed   = fromKtToGameUnit(maxPlaneSpeedKt);    //Irrlicht unit
    const float flatStallSpeed  = fromKtToGameUnit(flatStallSpeedKt);   //Irrlicht unit

    //Init plane limits values
    float loadFactor = 1.0f;    //No unit
    float stallSpeed = -100.0f; //Irrlicht unit

    //Init moving plane values
    float planeWeight     = voidPlaneWeightKg;
    float planeSpeed      = 0.0f;
    float planeSpeedFloor = 0.0f;
    float planeAltitude   = 0.0f;
    float rotationAngle   = 0.0f;

    float motorPower = 0.0f;

    const float weight = planeWeight * g;

    float isBrakes   = true;
    float isStalling = false;
    float isCrashed  = false;

    bool onFloor    = false;
    bool inTakeOff  = false;
    bool inFlight   = true;
    bool inLanding  = false;

    /************************************************************************************/
    /******************************** Constructor ***************************************/
    /************************************************************************************/
    /* MyEventReceiver: struct constructor
     * Initialise all values of the table containing the state of the keys to false
     * (not clicked).
    */
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
    /* float fromKtToGameUnit: convert from Kt unit to irrlicht unit (kt = 1.852 km/h)
     * params:  float valueToConvert:      the value in Kt unit
     * return:  float:  the value converted
    */
    float fromKtToGameUnit(float valueToConvert)
    {
        return valueToConvert / 400.0f;
    }

    /* float fromGameUnitToKt: convert from irrlicht unit to Kt unit (kt = 1.852 km/h)
     * params:  float valueToConvert:      the value in irrlicht unit
     * return:  float:  the value converted
    */
    float fromGameUnitToKt(float valueToConvert)
    {
        return valueToConvert * 400.0f;
    }

    /* void planeOnFloor:  Calculate the position of the plane and change it direction during the "on floor" phase.
     *                      Do all the computation for the first phase of the take off
     * params:  is::ISceneNode *node:   Instance of the global plane node
     *                                  (permit only to change the plane direction)
    */
    void planeOnFloor(is::ISceneNode *node)
    {
        //Brakes used only on the plane wheels
        if(keyIsDown[KEY_KEY_P] == true)
            isBrakes = !isBrakes;

        if(!isBrakes)
        {
            ic::vector3df childRotation = node->getRotation();

            if(keyIsDown[KEY_UP] == true)
            {
                if(planeSpeed < maxPlaneSpeed)
                {
                    planeSpeed += speedStep;
                    planeSpeedFloor = planeSpeed;
                }
            }
            if(keyIsDown[KEY_DOWN] == true)
            {
                if(planeSpeed > minPlaneSpeed)
                {
                    planeSpeed -= speedStep;
                    planeSpeedFloor = planeSpeed;
                }
            }

            if(keyIsDown[KEY_KEY_Z] == true)
                childRotation.X -= altitudeAngleStep;
            if(keyIsDown[KEY_KEY_S] == true)
            {
                childRotation.X += altitudeAngleStep;
                if(childRotation.X >=2 )
                {
                    onFloor = false;
                    isCrashed = true;
                }
            }

            if(keyIsDown[KEY_KEY_D] == true)
                rotationAngle  += rotationAngleStep;
            if(keyIsDown[KEY_KEY_Q] == true)
                rotationAngle  -= rotationAngleStep;

            node->setRotation(childRotation);
        }
    }

    /* void planeInTakeOff:  Calculate the position of the plane and change it direction during the critical pahse of the take off.
     *                       All changed datas between 0 and 15 meters
     * params:  is::ISceneNode *node:   Instance of the global plane node
     *                                  (permit only to change the plane direction)
    */
    void planeInTakeOff(is::ISceneNode *node)
    {
        ic::vector3df childRotation = node->getRotation();

        if(keyIsDown[KEY_UP] == true)
        {
        }
        if(keyIsDown[KEY_DOWN] == true)
        {
        }

        if(keyIsDown[KEY_KEY_Z] == true)
        if(keyIsDown[KEY_KEY_S] == true)
        {
        }

        if(keyIsDown[KEY_KEY_D] == true)
        {
        }
        if(keyIsDown[KEY_KEY_Q] == true)
        {
        }
    }

    /* void planeInFlight:  Calculate the position of the plane and change it direction.
     *                  All changed data s will be called by the main when nedded
     * params:  is::ISceneNode *node:   Instance of the global plane node
     *                                  (permit only to change the plane direction)
    */
    void planeInFlight(is::ISceneNode *node)
    {
        if(stallSpeed < planeSpeed && stallSpeed * 1.1 > planeSpeed)
        {
        }
        if(stallSpeed >= planeSpeed)
        {
        }
        //Increase or decrease the plane speed
        ic::vector3df childRotation = node->getRotation();

        if(keyIsDown[KEY_UP] == true)
        {
            //plane speed = valeur de vitesse absolue de l'avion
            // A mettre en paralèlle avec la puissance du moteur, le poids ...
            if(motorPower < maxMotorPower)
            {
                motorPower += motorStep;
            }
        }
        if(keyIsDown[KEY_DOWN] == true)
        {
            if(motorPower > minMotorPower)
            {
                motorPower -= motorStep;
            }
        }

        //Get the plane up or down
        if(keyIsDown[KEY_KEY_Z] == true)
            childRotation.X -= altitudeAngleStep;
        if(keyIsDown[KEY_KEY_S] == true)
            childRotation.X += altitudeAngleStep;

        //Open the side panels of the plane to turn to the right or the left
        if(keyIsDown[KEY_KEY_D] == true)
        {
            //TD: Add the wind effect
            //If the plane is flat (not in the wrong inclinaison)
            if(childRotation.Z <= 0)
                childRotation.Z -= rotationAngleStep;
            else
                childRotation.Z -= 2 * rotationAngleStep;
        }
        if(keyIsDown[KEY_KEY_Q] == true)
        {
            if(childRotation.Z >= 0)
                childRotation.Z += rotationAngleStep;
            else
                childRotation.Z += 2 * rotationAngleStep;
        }

        node->setRotation(childRotation);

        std::cout<<"motor power : "<<motorPower<<std::endl;

        if(planeSpeed < motorPower)
            planeSpeed += 1/planeWeight * motorPower;
        if(planeSpeed > motorPower)
            planeSpeed -= 1/planeWeight * motorPower;

        std::cout<<"factor : "<<childRotation.X<<std::endl;

        if(childRotation.X > 0)
        {
            planeSpeed = (1 - childRotation.X / 90) * planeSpeed;
            planeSpeedFloor = cos(childRotation.X * core::DEGTORAD) * planeSpeed;
        }
        else if(childRotation.X == 0)
            planeSpeedFloor = planeSpeed;
        else if(childRotation.X > 0)
        {
            planeSpeed = (1 - childRotation.X / 90) * planeSpeed;
            planeSpeedFloor = planeSpeed + cos(childRotation.X * core::DEGTORAD) * planeSpeed;
        }
        planeAltitude  -= sin(childRotation.X * core::DEGTORAD) * planeSpeed;


        std::cout<<"plane speed : "<<planeSpeed<<std::endl;
        std::cout<<"plane altitude : "<<planeSpeed<<std::endl;

        //Compute rotation
        float planeSpeedMByS = fromGameUnitToKt(planeSpeed) * 1.852 * 0.277777777778;
        if(planeSpeedMByS > 0)
            rotationAngle -= (tan(childRotation.Z * core::DEGTORAD) * g / planeSpeedMByS) * core::RADTODEG / 20; // for real values /80

        //Compute the stall speed
        loadFactor = (1/cos(-childRotation.Z*core::DEGTORAD));
        stallSpeed = sqrt(loadFactor) * flatStallSpeed;
    }

    /* void planeInLanding:  Calculate the position of the plane and change it direction during the critical pahse of the landing.
     *                       All changed datas between 0 and 15 meters
     * params:  is::ISceneNode *node:   Instance of the global plane node
     *                                  (permit only to change the plane direction)
    */
    void planeInLanding(is::ISceneNode *node)
    {
        ic::vector3df childRotation = node->getRotation();

        if(keyIsDown[KEY_UP] == true)
        {
        }
        if(keyIsDown[KEY_DOWN] == true)
        {
        }

        if(keyIsDown[KEY_KEY_Z] == true)
        if(keyIsDown[KEY_KEY_S] == true)
        {
        }

        if(keyIsDown[KEY_KEY_D] == true)
        {
        }
        if(keyIsDown[KEY_KEY_Q] == true)
        {
        }
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
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Z && !keyIsDown[KEY_KEY_Z]) // Go up
            {
                keyIsDown[KEY_KEY_Z] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Z && keyIsDown[KEY_KEY_Z])
            {
                keyIsDown[KEY_KEY_Z] = false;
            }
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_S && !keyIsDown[KEY_KEY_S]) // Go down
            {
                keyIsDown[KEY_KEY_S] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_S)
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
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_UP && !keyIsDown[KEY_UP]) // Higher engine speed
            {
                keyIsDown[KEY_UP] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_UP)
            {
                keyIsDown[KEY_UP] = false;
            }
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_DOWN && !keyIsDown[KEY_DOWN]) // Lower engine speed
            {
                keyIsDown[KEY_DOWN] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_DOWN)
            {
                keyIsDown[KEY_DOWN] = false;
            }
            if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_P && !keyIsDown[KEY_KEY_P]) // Unlock or lock brakes
            {
                keyIsDown[KEY_KEY_P] = true;
            }
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_P)
            {
                keyIsDown[KEY_KEY_P] = false;
            }
        }

        return false;
    }
};

void manageCollisionsWithScenery(is::ISceneManager *smgr,
                                 is::IMesh *city_mesh,
                                 is::ISceneNode* city_node,
                                 is::IAnimatedMeshSceneNode *plane,
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

    //City
    is::IMesh *city_mesh = smgr->getMesh("data/city/city_cercles.obj");
    is::ISceneNode *city_node;
    city_node = smgr->addOctreeSceneNode(city_mesh,nullptr,-1,1024);
    city_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    city_node->setScale(ic::vector3df(10,10,10));

    //Init the object plane
    is::IAnimatedMesh *plane_mesh = smgr->getMesh("data/plane/plane.obj");
    is::IAnimatedMesh *screw_mesh = smgr->getMesh("data/plane/screw2.obj");
    is::ISceneNode *parentNode = smgr->addEmptySceneNode();
    is::ISceneNode *parentRotationNode = smgr->addEmptySceneNode();
    is::IAnimatedMeshSceneNode *plane_node= smgr->addAnimatedMeshSceneNode(plane_mesh);
    is::IAnimatedMeshSceneNode *screw_node= smgr->addAnimatedMeshSceneNode(screw_mesh);
    parentRotationNode->setParent(parentNode);
    plane_node->setParent(parentRotationNode);
    plane_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    plane_node->setScale(ic::vector3df(0.05,0.05,0.05));
    screw_node->setParent(parentRotationNode);
    screw_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    screw_node->setScale(ic::vector3df(0.05,0.05,0.05));
    screw_node->setPosition(ic::vector3df(0.0,0.25,0.35));

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

    // 2D elements initialization
    guiManager->initialize2DElements();

    // Collision management with scenery
    manageCollisionsWithScenery(smgr, city_mesh, city_node, plane_node, parentNode);

    float planeWeigth = 1000.0f;
    receiver.setPlaneWeight(planeWeigth);

    float planeSpeed    = 0.0f;
    float planeAltitude = 0.0f;
    float rotAngle      = 0.0f;

    while(device->run())
    {
        //Update 2D elements
        std::vector<CGUICompass*> compasses = guiManager->update2DElements();

        //If the plane is flying then
        //  inFlight = true
        //Else, ie. plane on the ground, in take-off position and in landing position
        //  inFlight = false
        ic::vector3df rotation = parentNode->getRotation();
        ic::vector3df position = parentNode->getPosition();

        ic::vector3df rotation_screw = screw_node->getRotation();

        if(receiver.onFloor)
        {
            receiver.planeOnFloor(parentRotationNode);

            rotation.Y      = receiver.getRotation();
            planeSpeed      = receiver.getSpeed();

            position.X += planeSpeed * sin(rotation.Y * M_PI / 180.0);
            position.Z += planeSpeed * cos(rotation.Y * M_PI / 180.0);
        }
        else if(receiver.inTakeOff)
        {
            std::cout<<"TD : plane is taking off"<<std::endl;
        }
        else if(receiver.inFlight)
        {
            receiver.planeInFlight(parentRotationNode);

            rotation.Y      = receiver.getRotation();
            planeSpeed      = receiver.getSpeed();
            planeAltitude   = receiver.getAltitude();

            position.X += planeSpeed * sin(rotation.Y * M_PI / 180.0);
            position.Z += planeSpeed * cos(rotation.Y * M_PI / 180.0);
            position.Y  = planeAltitude;

            rotation_screw.Z += 30.0;
        }
        else if(receiver.inLanding)
        {
            std::cout<<"TD : plane is landing"<<std::endl;
        }
        else if(receiver.isStalling)
        {
            std::cout<<"TD : the plane is stalling"<<std::endl;
        }
        else
        {
            std::cout<<"TD : the plane has crashed"<<std::endl;            
        }

        parentNode->setRotation(rotation);
        parentNode->setPosition(position);
        screw_node->setRotation(rotation_screw);

        //Camera position
        smgr->addCameraSceneNode(plane_node, ic::vector3df(0, 18, -34), parentNode->getPosition());

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
