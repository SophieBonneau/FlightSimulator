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
    ~Scene(){}

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
    /* void initializeIrrlicht:  Initialization of the irrlicht parameters: event receiver, device, scene manager, gui.
    */
    void initializeIrrlicht();

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
    irr::IrrlichtDevice *m_device;
    irr::scene::ISceneManager* m_smgr;
    irr::video::IVideoDriver *m_driver;
    GUIElements* m_guiManager;

    // Scene objects
    irr::scene::ISceneNode *m_parentNode;
    irr::scene::ISceneNode *m_parentRotationNode;
    Screw* m_screw;
    Wing* m_leftWing;
    Wing* m_rightWing;
    Tail* m_middleTail;
    Tail* m_leftTail;
    Tail* m_rightTail;
    Body* m_body;
    Fire* m_fire;
    irr::gui::IGUIEnvironment *m_gui;
    irr::scene::ICameraSceneNode *m_camera;
    irr::scene::ISceneNode *m_cameraTarget;

    //Gui
    std::vector<CGUICompass*> m_compasses;

    //Collision
    irr::scene::ISceneNodeAnimatorCollisionResponse *m_animCollision;

    // Event objects
    EventReceiver *m_receiver;

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
