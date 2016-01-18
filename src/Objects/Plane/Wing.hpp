#pragma once

#ifndef WING
#define WING

#include "irrlicht.h"
#include "PlaneElement.hpp"


class Wing : public PlaneElement
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    /* Constructor Wing: Initialize all global attributes of the classe. It also update specified wings attributs:
     *                      scale, initial position of the mesh.
     * params:   irr::scene::ISceneManager* smgr: the application scene manager
                 irr::scene::ISceneNode *parentRotationNode: the general parent used for the global intern rotation of the plane
                 irr::io::path meshPath: the path to the wing mesh
    */
    Wing(irr::scene::ISceneManager*, irr::scene::ISceneNode *parentRotationNode, irr::io::path meshPath);

};

#endif
