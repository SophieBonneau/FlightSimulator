#pragma once

#ifndef BODY
#define BODY

#include "irrlicht.h"
#include "PlaneElement.hpp"

/* Class Body: Herit from the PLane element class. Manage the body of the plane has an irrlicht node.
*/

class Body : public PlaneElement
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    /* Constructor Body: Initialize all global attributes of the classe and the specified parameters:
     *                      scale, initial position of the mesh.
     * params:   irr::scene::ISceneManager*: the application scene manager
                 irr::scene::ISceneNode *: the general parent used for the global intern rotation of the plane
                 irr::io::path: the path to the body mesh
    */
    Body(irr::scene::ISceneManager*, irr::scene::ISceneNode*, irr::io::path);

};

#endif
