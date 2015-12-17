#include <irrlicht.h>

#include <iostream>
#include <time.h>
#include <vector>


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
            std::cout<<"bla Q"<<std::endl;
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

int main()
{
  // Le gestionnaire d'événements
  MyEventReceiver receiver;
  // Création de la fenêtre et du système de rendu.
  IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                        ic::dimension2d<u32>(640, 480),
                                        16, false, false, false, &receiver);

  iv::IVideoDriver  *driver = device->getVideoDriver();
  is::ISceneManager *smgr = device->getSceneManager();
  ig::IGUIEnvironment *gui  = device->getGUIEnvironment();

  //City
  device->getFileSystem()->addFileArchive("data/city.zip");
  is::IAnimatedMesh *city_mesh = smgr->getMesh("city.obj");
  is::ISceneNode *city_node;
  city_node = smgr->addOctreeSceneNode(city_mesh->getMesh(0),nullptr,-1,1024);
  city_node->setMaterialFlag(iv::EMF_LIGHTING,false);
  city_node->setScale(ic::vector3df(100,100,100));
  city_node->setPosition(ic::vector3df(-1000,-500, 100));

  //Plane
  device->getFileSystem()->addFileArchive("data/plane.zip");
  is::IAnimatedMesh *plane_mesh = smgr->getMesh("Cessna172.obj");
  is::IAnimatedMeshSceneNode *plane_node = smgr->addAnimatedMeshSceneNode(plane_mesh);
  plane_node->setMaterialFlag(iv::EMF_LIGHTING,false);

  //Step
  float step = 2.0f;
  receiver.setStep(step);

  //Camera
  smgr->addCameraSceneNodeFPS();

  //Water
  is::IAnimatedMesh *mesh_water = smgr->addHillPlaneMesh( "myHill",
         core::dimension2d<f32>(20,20),
         core::dimension2d<u32>(200,200), 0, 0,
         core::dimension2d<f32>(0,0),
         core::dimension2d<f32>(20,20));
  scene::ISceneNode* plan_water = smgr->addWaterSurfaceSceneNode(mesh_water->getMesh(0), 1.0f, 500.0f, 30.0f);
  plan_water->setMaterialTexture(0, driver->getTexture("data/water.jpg"));
  plan_water->setMaterialFlag(iv::EMF_LIGHTING, false);
  plan_water->setMaterialType(video::EMT_REFLECTION_2_LAYER);
  float water_initial_position = -6.0f;
  float water_position = water_initial_position;
  plan_water->setPosition(ic::vector3df(-1000,-502, 100));

  while(device->run())
  {
    //Movements of the plane
    receiver.MovePlane(plane_node);

    // Back color
    driver->beginScene(true,true,iv::SColor(100,150,200,255));

    // Draw the scene
    smgr->drawAll();
    gui->drawAll();
    driver->endScene();
  }

  device->drop();

  return 0;
}
