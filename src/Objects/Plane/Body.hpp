#pragma once

#ifndef BODY
#define BODY

#include "irrlicht.h"

#include "PlaneElement.hpp"


class Body : public PlaneElement
{
public:
    // Constructor
    Body(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode *parentRotationNode, irr::io::path meshPath);
    // Destructor
    ~Body(){}

    // To initialize mesh and node
    void initialize();

};

#endif
