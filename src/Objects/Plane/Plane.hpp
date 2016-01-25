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
    /******************************** Constructors**************************************/
    /************************************************************************************/
    /* Constructor Plane: Initialize the global attributes and every plane elements:
     *                      screw, two wings, 3 tails and the body.
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


    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/

    /* irr::scene::ISceneNode * getParentNode: getter for the plane parent node, used for the plane position and rotation on the Y axis
    */
    irr::scene::ISceneNode * getParentNode() const    {   return m_parentNode; }


    /* irr::scene::ISceneNode * getParentNode: getter for the plane parent node, used for the plane position and rotation on the X and Z axis
    */
    irr::scene::ISceneNode * getParentRotationNode() const     {   return m_parentRotationNode; }

    /* Screw* getScrew: getter for the plane screw object
    */
    Screw* getScrew() const     {   return m_screw; }

    /* Wing* getLeftWing: getter for the plane left wing object
    */
    Wing* getLeftWing() const     {   return m_leftWing; }

    /* Wing* getRightWing: getter for the plane right wing object
    */
    Wing* getRightWing() const     {   return m_rightWing; }

    /* Tail* getMiddleTail: getter for the plane middle tail object
    */
    Tail* getMiddleTail() const     {   return m_middleTail; }

    /* Tail* getLeftTail: getter for the plane left tail object
    */
    Tail* getLeftTail() const     {   return m_leftTail; }

    /* Tail* getRightTail: getter for the plane right tail object
    */
    Tail* getRightTail() const     {   return m_rightTail; }

    /* Body* getBody: getter for the plane body object
    */
    Body* getBody() const     {   return m_body; }

    /* float getPlaneSpeed: getter for the plane current speed in km/h
    */
    float getPlaneSpeed() const { return m_planeSpeed;}

    /* float getPlaneSpeed: getter for the plane current altitude in meters
    */
    float getPlaneAltitude() const { return m_planeAltitude;}

    /* void setPlaneSpeed: set the plane current speed in km/h
    * params:  const float planeSpeed
    */
    void setPlaneSpeed(const float& planeSpeed) { m_planeSpeed = planeSpeed;}

    /* void setPlaneAltitude: set the plane current altitude in meters
    * params:  const float planeAltitude
    */
    void setPlaneAltitude(const float& planeAltitude) { m_planeAltitude = planeAltitude;}

    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/

    void computeNewPosition(irr::core::vector3df rotation);

private:

    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/

    // Render object
    irr::scene::ISceneManager* m_smgr;

    // Plane objects
    irr::scene::ISceneNode *m_parentNode = nullptr;
    irr::scene::ISceneNode *m_parentRotationNode = nullptr;
    Screw* m_screw = nullptr;
    Wing* m_leftWing = nullptr;
    Wing* m_rightWing = nullptr;
    Tail* m_middleTail = nullptr;
    Tail* m_leftTail = nullptr;
    Tail* m_rightTail = nullptr;
    Body* m_body = nullptr;

    // Plane characteristics
    float m_planeSpeed;
    float m_planeAltitude;
};

#endif
