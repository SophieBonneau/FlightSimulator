#pragma once

#ifndef WING
#define WING

#include "irrlicht.h"
#include "PlaneElement.hpp"


class Wing : public PlaneElement
{
public:
    // Constructor
    Wing(irr::scene::ISceneManager*, irr::scene::ISceneNode *parentRotationNode, irr::io::path meshPath);
    // Destructor
    ~Wing(){}

    // To initialize mesh and node
    void initialize();

};

#endif
