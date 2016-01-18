#pragma once

#ifndef TAIL
#define TAIL

#include "irrlicht.h"
#include "PlaneElement.hpp"


class Tail : public PlaneElement
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    /* Constructor Tail: Initialize all global attributes of the classe. It also update specified tail attributs:
     *                      scale, initial position of the mesh.
     * params:   irr::scene::ISceneManager* smgr: the application scene manager
                 irr::scene::ISceneNode *parentRotationNode: the general parent used for the global intern rotation of the plane
                 irr::io::path meshPath: the path to the tail mesh
    */
    Tail(irr::scene::ISceneManager*, irr::scene::ISceneNode *parentRotationNode, irr::io::path meshPath);

};

#endif
