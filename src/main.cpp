#include <irrlicht.h>
#include <iostream>
#include <time.h>
#include <vector>

#include "CGUICompass.hpp"

using namespace irr;
namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


struct MyEventReceiver : IEventReceiver
{
    is::IAnimatedMeshSceneNode *node;
    is::ISceneNode *parentNode;
    bool keyIsDown[KEY_KEY_CODES_COUNT];

    float speedStep;
    float rotStep;
    float altitudeStep;

    float planeSpeed    = 0;
    float planeAltitude = 0;

    /************************************************************************************/
    /******************************** Constructor ***************************************/
    /************************************************************************************/
    MyEventReceiver()
    {
        for(unsigned int i = 0; i<KEY_KEY_CODES_COUNT; ++i)
        {
            keyIsDown[i] = false;
        }
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
    float getSpeed(){    return planeSpeed;  }

    /* void setSteps: function used to initialize the increase and decrease step of different parameters
     * params:  const float speedStep:      the step used to increase and decrese the plane speed
     *          const float rotStep:        the step used to turn the plane to the left or to the right
     *          const float altitudeStep:   the step used to increase and decrese the plane altitude
    */
    void setSteps(const float speedStep, const float rotStep, const float altitudeStep)
    {
        this->speedStep     = speedStep;
        this->rotStep       = rotStep;
        this->altitudeStep  = altitudeStep;
    }

    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/
    void movePlane(is::IAnimatedMeshSceneNode *node, is::ISceneNode *parentNode)
    {
        //Increase or decrease the plane speed
        ic::vector3df childRotation = node->getRotation();
        ic::vector3df parentRotation = parentNode->getRotation();

        if(keyIsDown[KEY_KEY_Z] == true)
        {
            if(planeSpeed < 0.5)
                planeSpeed += speedStep;
            else
                std::cout<<"Your plane is already at the highest speed !"<<std::endl;
        }
        if(keyIsDown[KEY_KEY_S] == true)
        {
            std::cout<<"TD : decrease the plane speed"<<std::endl;
            if(planeSpeed > 0)
                planeSpeed -= speedStep;
            else
                std::cout<<"Your plane has already stop !"<<std::endl;
        }

        //Open the side panels of the plane to turn to the right or the left
        if(keyIsDown[KEY_KEY_D] == true)
        {
            parentRotation.Y += rotStep;
            childRotation.Z -= 0.1;
            parentNode->setRotation(parentRotation);
            node->setRotation(childRotation);
        }
        if(keyIsDown[KEY_KEY_D] == false)
        {
            //parentRotation.Y += rotStep;
            if(childRotation.Z < 0) {
                childRotation.Z += 0.1;
            }
            parentNode->setRotation(parentRotation);
            node->setRotation(childRotation);

        }
        if(keyIsDown[KEY_KEY_Q] == true)
        {
            std::cout<<"TD : Turn the plane to the left"<<std::endl;
            parentRotation.Y -= rotStep;
            childRotation.Z  += 0.1;
            parentNode->setRotation(parentRotation);
            node->setRotation(childRotation);
        }
        if(keyIsDown[KEY_KEY_Q] == false)
        {
            //parentRotation.Y += rotStep;
            if(childRotation.Z > 0) {
                childRotation.Z -= 0.1;
            }
            parentNode->setRotation(parentRotation);
            node->setRotation(childRotation);

        }

        //Get the plane up or down
        if(keyIsDown[KEY_KEY_A] == true)
        {
            if(planeAltitude < 60)
            {
                planeAltitude += altitudeStep;
                if(childRotation.X > -45)
                {
                    childRotation.X -= 0.1;
                    node->setRotation(childRotation);
                    std::cout<<"badass values"<<childRotation.X<<std::endl;
                }
            }
            else
            {
                if(childRotation.X < 0)
                {
                    childRotation.X += 0.1;
                    node->setRotation(childRotation);
                    std::cout<<"Your plane is already at the highest altitude !"<<std::endl;
                }
            }
        }
        else if(childRotation.X < 0)
        {
            childRotation.X += 0.1;
            node->setRotation(childRotation);
            std::cout<<"Your plane is already at the highest altitude !"<<std::endl;
        }
        if(keyIsDown[KEY_KEY_E] == true)
        {
            if(planeAltitude > 0)
            {
                planeAltitude -= altitudeStep;
                if(childRotation.X < 45)
                {
                    childRotation.X += 0.1;
                    node->setRotation(childRotation);
                }
            }
            else
            {
                if(childRotation.X > 0)
                {
                    childRotation.X -= 0.1;
                    node->setRotation(childRotation);
                    std::cout<<"Your plane is already on the floor !"<<std::endl;
                }
            }
        }
        else if(childRotation.X > 0)
        {
            childRotation.X -= 0.1;
            node->setRotation(childRotation);
            std::cout<<"Your plane is already on the floor !"<<std::endl;
        }

        //Rear or unrear the plane
        if(keyIsDown[KEY_KEY_P] == true)
        {
            std::cout<<"TD : rear the plane"<<std::endl;
        }
        else
        {
            //std::cout<<"TD : unrear the plane"<<std::endl;
        }
        /*node->setPosition(position);
        node->setRotation(rotation);*/


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
int main()
{
    // display values
    int wind_speed = 20;
    int altitude = 1000;
    int vertical_speed = -20;

    // Le gestionnaire d'événements
    MyEventReceiver receiver;

    // Création de la fenêtre et du système de rendu.
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d<u32>(640, 480),
                                          16, false, false, false, &receiver);
    iv::IVideoDriver *driver = device->getVideoDriver();
    is::ISceneManager *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui = device->getGUIEnvironment();

    //Init the object landscape
    is::IMesh *city_mesh = smgr->getMesh("data/city/city_cercles.obj");
    is::ISceneNode *city_node;
    city_node = smgr->addOctreeSceneNode(city_mesh,nullptr,-1,1024);
    city_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    city_node->setScale(ic::vector3df(10,10,10));

    //Init the object plane
    is::IAnimatedMesh *plane_mesh = smgr->getMesh("data/plane/Cessna172.obj");
    is::ISceneNode *parentNode = smgr->addEmptySceneNode();
    is::IAnimatedMeshSceneNode *plane_node= smgr->addAnimatedMeshSceneNode(plane_mesh);
    plane_node->setParent(parentNode);
    plane_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    plane_node->setScale(ic::vector3df(0.05,0.05,0.05));

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

    //Init steps
    float speedStep     = 0.01f;
    float rotStep       = 0.3f;
    float altitudeStep  = 0.1f;
    receiver.setSteps(speedStep, rotStep, altitudeStep);

    //2D elements
    // Compass
    iv::ITexture *texture_compass = driver->getTexture("data/2d/compass.png");
    ig::IGUIImage *image_compass = gui->addImage(ic::rect<s32>(10, 10, 80, 80));
    image_compass->setImage(texture_compass);
    image_compass->setScaleImage(true);
    // Level and arrows textures
    iv::ITexture *texture_level = driver->getTexture("data/2d/level.png");
    iv::ITexture *texture_arrows = driver->getTexture("data/2d/arrows.png");
    // Wind speed
    iv::ITexture *texture_wind_speed = driver->getTexture("data/2d/wind-speed.png");
    ig::IGUIImage *image_wind_speed = gui->addImage(ic::rect<s32>(10, 100, 120, 115));
    image_wind_speed->setImage(texture_wind_speed);
    image_wind_speed->setScaleImage(true);
    // Altitude
    iv::ITexture *texture_altitude = driver->getTexture("data/2d/altitude.png");
    ig::IGUIImage *image_altitude = gui->addImage(ic::rect<s32>(10, 120, 90, 135));
    image_altitude->setImage(texture_altitude);
    image_altitude->setScaleImage(true);
    // Vertical speed
    iv::ITexture *texture_vertical_speed = driver->getTexture("data/2d/vertical-speed.png");
    ig::IGUIImage *image_vertical_speed = gui->addImage(ic::rect<s32>(10, 140, 140, 155));
    image_vertical_speed->setImage(texture_vertical_speed);
    image_vertical_speed->setScaleImage(true);
    // Up/down plane
    iv::ITexture *texture_plane = driver->getTexture("data/2d/plane-up.png");
    CGUICompass* compass_plane = new CGUICompass(ic::rect<s32>(20,160,50,190), gui, nullptr);
    compass_plane->setCompassTexture(texture_plane);
    if(vertical_speed <0)
    {
        compass_plane->setCompassHeading(90);
    }

    //Numbers
    iv::ITexture *numbers[10];
    numbers[0] = driver->getTexture("data/2d/numbers/0.png");
    numbers[1] = driver->getTexture("data/2d/numbers/1.png");
    numbers[2] = driver->getTexture("data/2d/numbers/2.png");
    numbers[3] = driver->getTexture("data/2d/numbers/3.png");
    numbers[4] = driver->getTexture("data/2d/numbers/4.png");
    numbers[5] = driver->getTexture("data/2d/numbers/5.png");
    numbers[6] = driver->getTexture("data/2d/numbers/6.png");
    numbers[7] = driver->getTexture("data/2d/numbers/7.png");
    numbers[8] = driver->getTexture("data/2d/numbers/8.png");
    numbers[9] = driver->getTexture("data/2d/numbers/9.png");
    // Places for the wind speed
    int width = 10;
    int height = 11;
    int offset = 1;
    ig::IGUIImage *ws_10000 = gui->addImage(ic::rect<s32>(120+offset,112-height, 120+offset+width,112)); ws_10000->setScaleImage(true);
    ig::IGUIImage *ws_1000  = gui->addImage(ic::rect<s32>(120+offset + offset+width,112-height, 120+offset+width + offset+width,112)); ws_1000->setScaleImage(true);
    ig::IGUIImage *ws_100   = gui->addImage(ic::rect<s32>(120+offset + 2*(offset+width),112-height, 120+offset+width + 2*(offset+width),112)); ws_100->setScaleImage(true);
    ig::IGUIImage *ws_10    = gui->addImage(ic::rect<s32>(120+offset + 3*(offset+width),112-height, 120+offset+width + 3*(offset+width),112)); ws_10->setScaleImage(true);
    ig::IGUIImage *ws_1     = gui->addImage(ic::rect<s32>(120+offset + 4*(offset+width),112-height, 120+offset+width + 4*(offset+width),112)); ws_1->setScaleImage(true);
    // Places for the altitude
    ig::IGUIImage *a_10000 = gui->addImage(ic::rect<s32>(90+offset,133-height, 90+offset+width,133)); a_10000->setScaleImage(true);
    ig::IGUIImage *a_1000  = gui->addImage(ic::rect<s32>(90+offset + offset+width,133-height, 90+offset+width + offset+width,133)); a_1000->setScaleImage(true);
    ig::IGUIImage *a_100   = gui->addImage(ic::rect<s32>(90+offset + 2*(offset+width),133-height, 90+offset+width + 2*(offset+width),133)); a_100->setScaleImage(true);
    ig::IGUIImage *a_10    = gui->addImage(ic::rect<s32>(90+offset + 3*(offset+width),133-height, 90+offset+width + 3*(offset+width),133)); a_10->setScaleImage(true);
    ig::IGUIImage *a_1     = gui->addImage(ic::rect<s32>(90+offset + 4*(offset+width),133-height, 90+offset+width + 4*(offset+width),133)); a_1->setScaleImage(true);
    // Places for vertical speed
    ig::IGUIImage *vs_10000 = gui->addImage(ic::rect<s32>(140+offset,153-height, 140+offset+width,153)); vs_10000->setScaleImage(true);
    ig::IGUIImage *vs_1000  = gui->addImage(ic::rect<s32>(140+offset + offset+width,153-height, 140+offset+width + offset+width,153)); vs_1000->setScaleImage(true);
    ig::IGUIImage *vs_100   = gui->addImage(ic::rect<s32>(140+offset + 2*(offset+width),153-height, 140+offset+width + 2*(offset+width),153)); vs_100->setScaleImage(true);
    ig::IGUIImage *vs_10    = gui->addImage(ic::rect<s32>(140+offset + 3*(offset+width),153-height, 140+offset+width + 3*(offset+width),153)); vs_10->setScaleImage(true);
    ig::IGUIImage *vs_1     = gui->addImage(ic::rect<s32>(140+offset + 4*(offset+width),153-height, 140+offset+width + 4*(offset+width),153)); vs_1->setScaleImage(true);

    // Collision management
    scene::ITriangleSelector *selector_city;
    selector_city = smgr->createOctreeTriangleSelector(city_mesh, city_node);
    city_node->setTriangleSelector(selector_city);
    scene::ISceneNodeAnimator *anim_collision_plane_city;
    anim_collision_plane_city = smgr->createCollisionResponseAnimator(selector_city,
                                                 plane_node,
                                                 ic::vector3df(1.5, 1.5, 1.5), // radiuses
                                                 ic::vector3df(0, 0, 0),  // gravity
                                                 ic::vector3df(0, 0, 0));  // center offset
    plane_node->addAnimator(anim_collision_plane_city);

    float planeSpeed    = 0;
    float planeAltitude = 0;

    //Init the plane state
    //****************************** To change to false: true only for tests ***********************************************//
    bool inFlight = true;

    while(device->run())
    {
        //2D elements
        // Horizontal level
        CGUICompass* compass_level = new CGUICompass(ic::rect<s32>(device->getVideoDriver()->getScreenSize().Width/2 - 40,
                                                             device->getVideoDriver()->getScreenSize().Height/2 - 30,
                                                             device->getVideoDriver()->getScreenSize().Width/2 + 40,
                                                             device->getVideoDriver()->getScreenSize().Height/2 + 30), gui, nullptr);
        compass_level->setCompassTexture(texture_level);
        compass_level->setCompassHeading(0);
        // Arrows
        CGUICompass* compass_arrows = new CGUICompass(ic::rect<s32>(10, 10, 80, 80), gui, nullptr);

        compass_arrows->setCompassTexture(texture_arrows);
        compass_arrows->setCompassHeading(50);
        // Wind speed number update
        ws_10000->setImage(numbers[(wind_speed / 10000) % 10]);
        ws_1000->setImage(numbers[(wind_speed / 1000) % 10]);
        ws_100->setImage(numbers[(wind_speed / 100) % 10]);
        ws_10->setImage(numbers[(wind_speed / 10) % 10]);
        ws_1->setImage(numbers[(wind_speed / 1) % 10]);
        // altitude number update
        a_10000->setImage(numbers[(altitude / 10000) % 10]);
        a_1000->setImage(numbers[(altitude / 1000) % 10]);
        a_100->setImage(numbers[(altitude / 100) % 10]);
        a_10->setImage(numbers[(altitude / 10) % 10]);
        a_1->setImage(numbers[(altitude / 1) % 10]);
        // vertical speed number update
        vs_10000->setImage(numbers[(abs(vertical_speed) / 10000) % 10]);
        vs_1000->setImage(numbers[(abs(vertical_speed) / 1000) % 10]);
        vs_100->setImage(numbers[(abs(vertical_speed) / 100) % 10]);
        vs_10->setImage(numbers[(abs(vertical_speed) / 10) % 10]);
        vs_1->setImage(numbers[(abs(vertical_speed) / 1) % 10]);
        // Update the plane orientation
        if(vertical_speed >= 0)
            compass_plane->setCompassHeading(0);
        else
            compass_plane->setCompassHeading(-55);

        //If the plane is flying then
        //  inFlight = true
        //Else, ie. plane on the ground, in take-off position and in landing position
        //  inFlight = false
        ic::vector3df position = parentNode->getPosition();
        ic::vector3df rotation = parentNode->getRotation();

        if(inFlight)
        {
            //Movements of the plane
            planeSpeed      = receiver.getSpeed();
            planeAltitude   = receiver.getAltitude();

            position.X += planeSpeed * sin(rotation.Y * M_PI / 180.0);
            position.Z += planeSpeed * cos(rotation.Y * M_PI / 180.0);
            position.Y  = planeAltitude;

            parentNode->setPosition(position);

            receiver.movePlane(plane_node, parentNode);
        }
        else
        {
            std::cout<<"TD : plane on the ground, in take-off position and in landing position"<<std::endl;
        }

        //Camera position
        smgr->addCameraSceneNode(plane_node, ic::vector3df(0, 18, -34), parentNode->getPosition());

        //Back color
        driver->beginScene(true,true,iv::SColor(100,150,200,255));
        //Draw the scene
        smgr->drawAll();
        gui->drawAll();
        compass_level->draw();
        compass_arrows->draw();
        compass_plane->draw();
        driver->endScene();
    }
    device->drop();
    return 0;

}
