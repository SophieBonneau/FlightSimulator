#pragma once

#ifndef SCREW
#define SCREW

#include "irrlicht.h"
#include "PlaneElement.hpp"
#include "iostream"

/* Class Screw: inherits from the PLaneElement class. Manage the screw of the plane has an irrlicht node.
*/
class Screw : public PlaneElement
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    /* Constructor Screw: Initialize the global attributes and the specified parameters: the wheel rotation step,
     *                      scale, initial position of the mesh
     * params:   irr::scene::ISceneManager*: the application scene manager
                 irr::scene::ISceneNode *: the general parent used for the global intern rotation of the plane
                 irr::io::path: the path to the tail mesh
    */
    Screw(irr::scene::ISceneManager*, irr::scene::ISceneNode*, irr::io::path);

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* void setRotationSpeed: Set the screw rotation speed
     * params:  const double rotationStep: the rotation step for the rotation speed calculation
    */
    void setRotationStep(const double rotationStep){    m_rotationStep = rotationStep;  }

    /* float getSpeed: getter for the rotation step used for the speed rotation of the screw
    */
    float getRotationStep() const {    return m_rotationStep;  }

    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/

    /* int updateRotation: to update the screw rotation while rendering
     * return:  int:  if ok (screw mesh exist)
     *                else 0 send a message in the console
    */
    int updateRotation();

private:
    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/
    float m_rotationStep;
};

#endif
