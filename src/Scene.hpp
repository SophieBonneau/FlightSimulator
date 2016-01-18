#pragma once

#ifndef SCENE
#define SCENE

#include "irrlicht.h"

#include "Event/EventReceiver.hpp"
#include "GUI/GUIElements.hpp"
#include "Objects/Plane/Screw.hpp"
#include "Objects/Surroundings/Water.hpp"
#include "Objects/Surroundings/Fire.hpp"
#include "Objects/Surroundings/City.hpp"
#include "Objects/Plane/Body.hpp"
#include "Objects/Plane/Wing.hpp"
#include "Objects/Plane/Tail.hpp"

class GUIElements;
class Scene
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    /* Constructor Scene: Initialize all global attributes of the classe: display values, plane attributes
    */
    Scene();
    ~Scene()
    {
        delete m_screw;
        delete m_leftWing;
        delete m_rightWing;
        delete m_middleTail;
        delete m_leftTail;
        delete m_rightTail;
        delete m_body;
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
     * return:  irr::IrrlichtDevice: the irrlicht device
    */
    irr::IrrlichtDevice * getDevice() const {return m_device; }

    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/
    /* void initializeIrrlicht: function to initilize Irrlicht object
    */
    void initializeIrrlicht();

    /* void initializeData: function to initialize objects
    */
    void initializeData();

    /* void render:  Global function used to render the application : gui, plane and surrondings
    */
    void render();

private:
    /* void manageCollisionsWithSurroundings: Manage the collision between the plane and all the surondings
    */
    void manageCollisionsWithSurroundings(irr::scene::IMesh *surroundingMesh, irr::scene::ISceneNode* surroundingNode);

    /* void initializeObjects: Initialize all meshs used, except the water: the plane, the landscape
    */
    void initializeObjects();

    /* void initializeGui: Initialize all object of the gui
    */
    void initializeGui();

    // Render objects
    irr::IrrlichtDevice *m_device = nullptr;
    irr::scene::ISceneManager* m_smgr = nullptr;
    irr::video::IVideoDriver *m_driver = nullptr;
    GUIElements* m_guiManager = nullptr;

    // Scene objects
    irr::scene::ISceneNode *m_parentNode = nullptr;
    irr::scene::ISceneNode *m_parentRotationNode = nullptr;
    Screw* m_screw = nullptr;
    Wing* m_leftWing = nullptr;
    Wing* m_rightWing = nullptr;
    Tail* m_middleTail = nullptr;
    Tail* m_leftTail = nullptr;
    Tail* m_rightTail = nullptr;
    Body* m_body = nullptr;
    Fire* m_fire = nullptr;
    City* m_city = nullptr;
    Water* m_water = nullptr;
    irr::gui::IGUIEnvironment *m_gui = nullptr;
    irr::scene::ICameraSceneNode *m_camera = nullptr;
    irr::scene::ISceneNode *m_cameraTarget = nullptr;

    //Gui
    std::vector<CGUICompass*> m_compasses;

    //Collision
    irr::scene::ISceneNodeAnimatorCollisionResponse *m_animCollision = nullptr;

    // Event objects
    EventReceiver *m_receiver = nullptr;

    // display values
    int m_wind_speed;
    int m_altitude;
    int m_vertical_speed;
    int m_gauge_offset;
    bool m_stall;

    float m_planeSpeed;
    float m_planeAltitude;
    float m_rotAngle;

    irr::core::vector3df m_cameraPose;
};

#endif
