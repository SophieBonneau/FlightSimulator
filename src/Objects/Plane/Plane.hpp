#pragma once

#ifndef PLANE
#define PLANE

#include "irrlicht.h"
#include "iostream"

#include "Screw.hpp"
#include "Body.hpp"
#include "Wing.hpp"
#include "Tail.hpp"

/* Class Plane: Manage the different elements of the plane has an irrlicht node.
*/
class Plane
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    /* Constructor Plane: Initialize the global attributes and the specified parameters:
     *                      scale, initial position of the mesh.
     * params:   irr::scene::ISceneManager*: the application scene manager
    */
    Plane(irr::scene::ISceneManager*);

    ~Plane()
    {
        delete m_screw;
        delete m_leftWing;
        delete m_rightWing;
        delete m_middleTail;
        delete m_leftTail;
        delete m_rightTail;
        delete m_body;
    }

    irr::scene::ISceneNode * getParentNode() const    {   return m_parentNode; }
    irr::scene::ISceneNode * getParentRotationNode() const     {   return m_parentRotationNode; }
    Screw* getScrew() const     {   return m_screw; }
    Wing* getLeftWing() const     {   return m_leftWing; }
    Wing* getRightWing() const     {   return m_rightWing; }
    Tail* getMiddleTail() const     {   return m_middleTail; }
    Tail* getLeftTail() const     {   return m_leftTail; }
    Tail* getRightTail() const     {   return m_rightTail; }
    Body* getBody() const     {   return m_body; }
    float getPlaneSpeed() const { return m_planeSpeed;}
    float getPlaneAltitude() const { return m_planeAltitude;}

    void setPlaneSpeed(const float& planeSpeed) { m_planeSpeed = planeSpeed;}
    void setPlaneAltitude(const float& planeAltitude) { m_planeAltitude = planeAltitude;}

    void computeNewPosition(irr::core::vector3df rotation);

private:
    irr::scene::ISceneManager* m_smgr;

    // Objects
    irr::scene::ISceneNode *m_parentNode = nullptr;
    irr::scene::ISceneNode *m_parentRotationNode = nullptr;
    Screw* m_screw = nullptr;
    Wing* m_leftWing = nullptr;
    Wing* m_rightWing = nullptr;
    Tail* m_middleTail = nullptr;
    Tail* m_leftTail = nullptr;
    Tail* m_rightTail = nullptr;
    Body* m_body = nullptr;


    float m_planeSpeed;
    float m_planeAltitude;
    float m_rotAngle;
};

#endif
