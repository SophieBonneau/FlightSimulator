#pragma once

#ifndef BODY
#define BODY

#include "irrlicht.h"

#include "PlaneElement.hpp"

using namespace irr;

class Body : public PlaneElement
{
public:
    // Constructor
    Body(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode *parentRotationNode, irr::io::path meshPath);
    // Destructor
    ~Body(){}

    // Setters and getters
    void setNode(irr::scene::IAnimatedMeshSceneNode* node){this->node = node; }
    irr::scene::IAnimatedMeshSceneNode* getNode() const {return this->node; }

    // To initialize mesh and node
    void initialize();

private:

    irr::scene::IAnimatedMeshSceneNode* node;

};

#endif
