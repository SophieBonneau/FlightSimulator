#pragma once

#ifndef WING
#define WING

#include "irrlicht.h"
#include "PlaneElement.hpp"
#include "iostream"

/* Class Wing: inherits from the PLaneElement class. Manage the wing of the plane has an irrlicht node.
*/
class Wing : public PlaneElement
{
public:
    /************************************************************************************/
    /******************************** Constructor **************************************/
    /************************************************************************************/
    /* Constructor Wing: Initialize the global attributes
     * params:   irr::scene::ISceneManager* smgr: the application scene manager
                 irr::scene::ISceneNode *parentRotationNode: the general parent used for the global intern rotation of the plane
                 irr::io::path meshPath: the path to the wing mesh
    */
    Wing(irr::scene::ISceneManager*, irr::scene::ISceneNode *parentRotationNode, irr::io::path meshPath);

};

#endif
