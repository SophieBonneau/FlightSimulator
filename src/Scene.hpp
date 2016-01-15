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

using namespace irr;
class GUIElements;
class Scene
{
public:
    // Constructor
    Scene();
    // Destructor
    ~Scene(){}

    // Getters and setters
    IrrlichtDevice * getDevice() const {return this->device; }

    void initializeIrrlicht();
    void initializeData();
    void render();


private:
    // Render objects
    IrrlichtDevice *device;
    irr::scene::ISceneManager* smgr;
    irr::video::IVideoDriver *driver;
    GUIElements* guiManager;

    // Scene objects
    irr::scene::ISceneNode *parentNode;
    irr::scene::ISceneNode *parentRotationNode;
    Screw* screw;
    Wing* leftWing;
    Wing* rightWing;
    Tail* middleTail;
    Tail* leftTail;
    Tail* rightTail;
    Body* body;
    irr::gui::IGUIEnvironment *gui;

    // Event objects
    EventReceiver *receiver;

    // display values
    int wind_speed;
    int altitude;
    int vertical_speed;
    int gauge_offset;
    bool stall;

    float planeSpeed;
    float planeAltitude;
    float rotAngle;


    void manageCollisionsWithSurroundings(irr::scene::ISceneManager *smgr,
                                     irr::scene::IMesh *city_mesh,
                                     irr::scene::ISceneNode* city_node,
                                     irr::scene::IMeshSceneNode *plane,
                                     irr::scene::ISceneNode *parentNode);


};

#endif
