#pragma once

#ifndef TAIL
#define TAIL

#include "irrlicht.h"
#include "PlaneElement.hpp"
#include "iostream"

/* Class Tail: inherits from the PLaneElement class. Manage the tail of the plane has an irrlicht node.
*/
class Tail : public PlaneElement
{
public:
    /************************************************************************************/
    /******************************** Constructor **************************************/
    /************************************************************************************/
    /* Constructor Tail: Initialize the global attributes
     * params:   irr::scene::ISceneManager* smgr: the application scene manager
                 irr::scene::ISceneNode *parentRotationNode: the general parent used for the global intern rotation of the plane
                 irr::io::path meshPath: the path to the tail mesh
    */
    Tail(irr::scene::ISceneManager*, irr::scene::ISceneNode *parentRotationNode, irr::io::path meshPath);

};

#endif
