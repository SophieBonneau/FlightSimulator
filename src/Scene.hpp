#pragma once

#ifndef SCENE
#define SCENE

#include "irrlicht.h"

#include "Event/EventReceiver.hpp"
#include "Objects/Plane/Screw.hpp"
#include "Objects/Surroundings/Water.hpp"
#include "Objects/Surroundings/City.hpp"
#include "Objects/Plane/Body.hpp"
#include "Objects/Plane/Wing.hpp"
#include "Objects/Plane/Tail.hpp"

class GUIElements;
class Scene
{
public:
    // Constructor
    Scene();
    // Destructor
    ~Scene(){}

    // Getters and setters
    irr::IrrlichtDevice * getDevice() const {return m_device; }

    void initializeIrrlicht();
    void initializeData();
    void render();

private:

    void manageCollisionsWithSurroundings(irr::scene::IMesh *city_mesh, irr::scene::ISceneNode* city_node);
    void initializeObjects();
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
    irr::gui::IGUIEnvironment *m_gui;

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


};

#endif
