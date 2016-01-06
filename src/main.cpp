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
    MyEventReceiver()
    {
        for(unsigned int i = 0; i<KEY_KEY_CODES_COUNT; ++i)
        {
            keyIsDown[i] = false;
        }
    }

    void MovePlane(is::IAnimatedMeshSceneNode *node)
    {
        ic::vector3df position = node->getPosition();
        ic::vector3df rotation = node->getRotation();
        if(keyIsDown[KEY_KEY_S] == true)
        {
            position.Z += -step * sin(rotation.Y * M_PI / 180.0);
            position.X += -step * cos(rotation.Y * M_PI / 180.0);
        }
        if(keyIsDown[KEY_KEY_Z] == true)
        {
            position.Z += step * sin(rotation.Y * M_PI / 180.0);
            position.X += step * cos(rotation.Y * M_PI / 180.0);
        }
        if(keyIsDown[KEY_KEY_Q] == true)
        {
            rotation.Y += step;
        }
        if(keyIsDown[KEY_KEY_D] == true)
        {
            rotation.Y -= 5;
        }
        node->setPosition(position);
        node->setRotation(rotation);
    }

    void setStep(const float step)
    {
        this->step = step;
    }

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
            if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Z) // Stop Avance
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
        }

        return false;
    }

    is::IAnimatedMeshSceneNode *node;
    float step;
    bool keyIsDown[KEY_KEY_CODES_COUNT];
};

void setGaugeOffset(int& gauge_offset, int percetage)
{
    if(percentage < 0 || percentage > 100)
    {
        std::cout<<"Error, the percentage must be between 0 and 100."<<std::endl;
    }
    else
    {

    }
}

int main()
{
    // display values
    int wind_speed = 20;
    int altitude = 1000;
    int vertical_speed = -20;
    int gauge_offset = 0;

    // Le gestionnaire d'événements
    MyEventReceiver receiver;

    // Création de la fenêtre et du système de rendu.
    IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                          ic::dimension2d<u32>(640, 480),
                                          16, false, false, false, &receiver);
    iv::IVideoDriver *driver = device->getVideoDriver();
    is::ISceneManager *smgr = device->getSceneManager();
    ig::IGUIEnvironment *gui = device->getGUIEnvironment();

    //City
    is::IMesh *city_mesh = smgr->getMesh("data/city_cercles.obj");
    is::ISceneNode *city_node;
    city_node = smgr->addOctreeSceneNode(city_mesh,nullptr,-1,1024);
    city_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    city_node->setScale(ic::vector3df(10,10,10));
    //city_node->setPosition(ic::vector3df(-1000,-500, 100));

    //Plane
    device->getFileSystem()->addFileArchive("data/plane.zip");
    is::IAnimatedMesh *plane_mesh = smgr->getMesh("Cessna172.obj");
    is::IAnimatedMeshSceneNode *plane_node = smgr->addAnimatedMeshSceneNode(plane_mesh);
    plane_node->setMaterialFlag(iv::EMF_LIGHTING,false);

    //Step
    float step = 2.0f;
    receiver.setStep(step);

    //Water
     is::IMesh *mesh_water = smgr->addHillPlaneMesh( "myHill",
           core::dimension2d<f32>(4.6,4.6),
           core::dimension2d<u32>(200,200), 0, 0,
           core::dimension2d<f32>(0,0),
           core::dimension2d<f32>(5,5));
    scene::ISceneNode* plan_water = smgr->addWaterSurfaceSceneNode(mesh_water, 0.2f, 500.0f, 10.0f);
    plan_water->setMaterialTexture(0, driver->getTexture("data/water.jpg"));
    plan_water->setMaterialFlag(iv::EMF_LIGHTING, false);
    plan_water->setMaterialType(video::EMT_REFLECTION_2_LAYER);
    //plan_water->setPosition(ic::vector3df(-1000,-502, 100));
    plan_water->setPosition(ic::vector3df(0,-2, 0));

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
    int height_u = 9;
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
    ig::IGUIImage *sign = gui->addImage(ic::rect<s32>(140+offset,153-height, 140+offset+width,153)); sign->setScaleImage(true);
    iv::ITexture *texture_plus = driver->getTexture("data/2d/+.png");
    iv::ITexture *texture_minus = driver->getTexture("data/2d/-.png");
    sign->setImage(texture_plus);
    ig::IGUIImage *vs_10000 = gui->addImage(ic::rect<s32>(140+offset+width,153-height, 140+offset+2*width,153)); sign->setScaleImage(true);vs_10000->setScaleImage(true);
    ig::IGUIImage *vs_1000  = gui->addImage(ic::rect<s32>(140+offset+width + offset+width,153-height, 140+offset+2*width + offset+width,153)); vs_1000->setScaleImage(true);
    ig::IGUIImage *vs_100   = gui->addImage(ic::rect<s32>(140+offset+width + 2*(offset+width),153-height, 140+offset+2*width + 2*(offset+width),153)); vs_100->setScaleImage(true);
    ig::IGUIImage *vs_10    = gui->addImage(ic::rect<s32>(140+offset+width + 3*(offset+width),153-height, 140+offset+2*width + 3*(offset+width),153)); vs_10->setScaleImage(true);
    ig::IGUIImage *vs_1     = gui->addImage(ic::rect<s32>(140+offset+width + 4*(offset+width),153-height, 140+offset+2*width + 4*(offset+width),153)); vs_1->setScaleImage(true);
    // Wind speed unity
    iv::ITexture *texture_wind_speed_u = driver->getTexture("data/2d/kmh.png");
    ig::IGUIImage *image_wind_speed_u = gui->addImage(ic::rect<s32>(120+offset+2*width + 4*(offset+width), 112-height, 120+offset+2*width+ 4*(offset+width)+40, 112));
    image_wind_speed_u->setImage(texture_wind_speed_u);
    image_wind_speed_u->setScaleImage(true);
    // Altitude unity
    iv::ITexture *texture_altitude_u = driver->getTexture("data/2d/m.png");
    ig::IGUIImage *image_altitude_u = gui->addImage(ic::rect<s32>(90+offset+2*width + 4*(offset+width),132-height_u, 90+offset+2*width + 4*(offset+width)+16,132));
    image_altitude_u->setImage(texture_altitude_u);
    image_altitude_u->setScaleImage(true);
    // Vertical speed unitys
    iv::ITexture *texture_vertical_speed_u = driver->getTexture("data/2d/ms.png");
    ig::IGUIImage *image_vertical_speed_u = gui->addImage(ic::rect<s32>(140+offset+3*width + 4*(offset+width),153-12, 140+offset+3*width + 4*(offset+width)+29,153));
    image_vertical_speed_u->setImage(texture_vertical_speed_u);
    image_vertical_speed_u->setScaleImage(true);
    // Gauge textures
    iv::ITexture *texture_gauge_empty = driver->getTexture("data/2d/gauge-empty.png");
    iv::ITexture *texture_gauge_full = driver->getTexture("data/2d/gauge-full.png");

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


    while(device->run())
    {
        //Camera position
        smgr->addCameraSceneNode(plane_node, ic::vector3df(-34, 18, 0), plane_node->getPosition()+ic::vector3df(0, 10, 0));

        //2D elements
        // Horizontal level
        CGUICompass* compass_level = new CGUICompass(ic::rect<s32>(device->getVideoDriver()->getScreenSize().Width/2 - 40,
                                                             device->getVideoDriver()->getScreenSize().Height/2 - 30,
                                                             device->getVideoDriver()->getScreenSize().Width/2 + 40,
                                                             device->getVideoDriver()->getScreenSize().Height/2 + 30), gui, nullptr);
        compass_level->setCompassTexture(texture_level);
        compass_level->setCompassHeading(0);
        // Gauge empty
        int gauge_width = 30;
        int gauge_height = 200;
        CGUICompass* compass_gauge_empty = new CGUICompass(ic::rect<s32>(device->getVideoDriver()->getScreenSize().Width -10 - gauge_width,
                                                                         10,
                                                                         device->getVideoDriver()->getScreenSize().Width -10,
                                                                         10 + gauge_height), gui, nullptr);
        compass_gauge_empty->setCompassTexture(texture_gauge_empty);
        //Gauge full
        CGUICompass* compass_gauge_full = new CGUICompass(ic::rect<s32>(device->getVideoDriver()->getScreenSize().Width -10 - gauge_width + 4,
                                                                         20 +2+gauge_offset,
                                                                         device->getVideoDriver()->getScreenSize().Width -10 -4,
                                                                         10 + gauge_height -2), gui, nullptr);
        compass_gauge_full->setCompassTexture(texture_gauge_full);

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
        // Update the 2d plane orientation and the vertical speed sign
        if(vertical_speed >= 0)
        {
            sign->setImage(texture_plus);
            compass_plane->setCompassHeading(0);
        }
        else
        {
            sign->setImage(texture_minus);
            compass_plane->setCompassHeading(-55);
        }


        //Movements of the plane
        receiver.MovePlane(plane_node);
        // Back color
        driver->beginScene(true,true,iv::SColor(100,150,200,255));
        // Draw the scene
        smgr->drawAll();
        gui->drawAll();
        compass_level->draw();
        compass_arrows->draw();
        compass_plane->draw();
        compass_gauge_empty->draw();
        compass_gauge_full->draw();
        driver->endScene();
    }
    device->drop();
    return 0;

}
