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


float rotation = 0.0;


struct MyEventReceiver : IEventReceiver
{
    is::IAnimatedMeshSceneNode *node;
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
    void movePlane(is::IAnimatedMeshSceneNode *node)
    {
        //Increase or decrease the plane speed
        ic::vector3df position = node->getPosition();
        ic::vector3df rotation = node->getRotation();
        if(keyIsDown[KEY_KEY_Z] == true)
        {
            if(planeSpeed < 5)
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
            std::cout<<"TD : Turn the plane to the right"<<std::endl;
            rotation.Y += rotStep;
        }
        if(keyIsDown[KEY_KEY_Q] == true)
        {
            std::cout<<"TD : Turn the plane to the left"<<std::endl;
            rotation.Y -= rotStep;
        }

        //Get the plane up or down
        if(keyIsDown[KEY_KEY_A] == true)
        {
            if(planeAltitude < 200)
                planeAltitude += altitudeStep;
            else
                std::cout<<"Your plane is already at the highest altitude !"<<std::endl;
        }
        if(keyIsDown[KEY_KEY_E] == true)
        {
            if(planeAltitude > 0)
                planeAltitude -= altitudeStep;
            else
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
        node->setPosition(position);
        node->setRotation(rotation);


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
    is::IAnimatedMeshSceneNode *plane_node = smgr->addAnimatedMeshSceneNode(plane_mesh);
    plane_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    plane_node->setScale(ic::vector3df(0.1,0.1,0.1));

    //Init the object water
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
    float rotStep       = 0.5f;
    float altitudeStep  = 0.5f;
    receiver.setSteps(speedStep, rotStep, altitudeStep);

    float planeSpeed    = 0;
    float planeAltitude = 0;

    //Init the plane state
    //****************************** To change to false: true only for tests ***********************************************//
    bool inFlight = true;

    while(device->run())
    {
        // Horizontal level
        /*CGUICompass* compass = new CGUICompass(ic::rect<s32>(device->getVideoDriver()->getScreenSize().Width/2 - 40,
                                                             device->getVideoDriver()->getScreenSize().Height/2 - 30,
                                                             device->getVideoDriver()->getScreenSize().Width/2 + 40,
                                                             device->getVideoDriver()->getScreenSize().Height/2 + 30), gui, nullptr);
        iv::ITexture *texture_level = driver->getTexture("data/2d/level.png");
        compass->setCompassTexture(texture_level);
        compass->setCompassHeading(0);*/

        //If the plane is flying then
        //  inFlight = true
        //Else, ie. plane on the ground, in take-off position and in landing position
        //  inFlight = false
        if(inFlight)
        {
            //Movements of the plane
            planeSpeed      = receiver.getSpeed();
            planeAltitude   = receiver.getAltitude();

            ic::vector3df position = plane_node->getPosition();
            ic::vector3df rotation = plane_node->getRotation();

            position.X += planeSpeed * sin(rotation.Y * M_PI / 180.0);
            position.Z += planeSpeed * cos(rotation.Y * M_PI / 180.0);
            position.Y = planeAltitude;

            plane_node->setPosition(position);

            receiver.movePlane(plane_node);
        }
        else
        {
            std::cout<<"TD : plane on the ground, in take-off position and in landing position"<<std::endl;
        }

        //Camera position
        smgr->addCameraSceneNode(plane_node, ic::vector3df(0, 18, -34), plane_node->getPosition());

        //Back color
        driver->beginScene(true,true,iv::SColor(100,150,200,255));
        //Draw the scene
        smgr->drawAll();
        gui->drawAll();
        //compass->draw();
        driver->endScene();
    }
    device->drop();
    return 0;

}
