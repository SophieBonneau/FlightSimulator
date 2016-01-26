#pragma once

#ifndef SCENE
#define SCENE

#include "irrlicht.h"
#include "iostream"

#include "Event/EventReceiver.hpp"
#include "GUI/GUIElements.hpp"
#include "Objects/Surroundings/Water.hpp"
#include "Objects/Surroundings/Fire.hpp"
#include "Objects/Surroundings/Landscape.hpp"
#include "Objects/Plane/Plane.hpp"
#include "Simulation/PlaneControl.hpp"

class GUIElements;
/* Class Scene: manage the objects, the Irrlicht rendering objects and the event objects creation,
 * the rendering of the scene and the collision management between the plane and surroundings
*/
class Scene
{
public:
    /************************************************************************************/
    /******************************** Constructor **************************************/
    /************************************************************************************/
    /* Constructor Scene: Initialize the global attributes
    */
    Scene();
    ~Scene()
    {
        delete m_fire;
        delete m_city;
        delete m_water;
        delete m_fire;
        delete m_receiver;
    }

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* irr::IrrlichtDevice getDevice: get the device from irrlicht for the application
    */
    irr::IrrlichtDevice * getDevice() const {return m_device; }

    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/
    /* void initializeIrrlicht: function to initialize Irrlicht object
    */
    void initializeIrrlicht();

    /* void initializeData: function to initialize objects
    */
    void initializeData();

    /* void render:  Global function used to render the application : gui, plane and surroundings
    */
    void render();

private:
    /* void manageCollisionsWithSurroundings: Manage the collision between the plane and surroundings, taking gravity into account or not
    */
    irr::scene::ISceneNodeAnimatorCollisionResponse* manageCollisionsWithSurroundings(Landscape *building, bool gravity);

    /* void initializeObjects: Initialize all meshs used
    */
    void initializeObjects();

    /* void initializeGui: Initialize every gui objects
    */
    void initializeGui();

    /* void updateGui: make the m_guiManager update the GUI objects according to the current simulation characteristics
    */
    void updateGui();

    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/
    // Render objects
    irr::IrrlichtDevice *m_device = nullptr;
    irr::scene::ISceneManager* m_smgr = nullptr;
    irr::video::IVideoDriver *m_driver = nullptr;
    GUIElements* m_guiManager = nullptr;

    // Scene objects
    Plane* m_plane = nullptr;
    Fire* m_fire = nullptr;
    Landscape* m_city = nullptr;
    Water* m_water = nullptr;
    irr::gui::IGUIEnvironment *m_gui = nullptr;
    irr::scene::ICameraSceneNode *m_camera = nullptr;
    irr::scene::ISceneNode *m_cameraTarget = nullptr;

    //Gui
    std::vector<CGUICompass*> m_compasses;

    //Collision
    irr::scene::ISceneNodeAnimatorCollisionResponse *m_animCollision        = nullptr;
    irr::scene::ISceneNodeAnimatorCollisionResponse *m_animCollisionAirport = nullptr;
    irr::scene::ISceneNodeAnimatorCollisionResponse *m_animCollisionCity    = nullptr;
    irr::scene::ISceneNodeAnimatorCollisionResponse *m_animCollisionRunway  = nullptr;
    irr::scene::ISceneNodeAnimatorCollisionResponse *m_animCollisionRunway2 = nullptr;

    // Event objects
    EventReceiver *m_receiver = nullptr;

    // Simulation objects
    PlaneControl* m_planeControl = nullptr;

    // display values
    int m_wind_speed;
    int m_altitude;
    int m_vertical_speed;
    int m_gauge_offset;
    bool m_stall;

    irr::core::vector3df m_cameraPose;
};

#endif
