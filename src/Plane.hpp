#pragma once

#ifndef PLANE
#define PLANE

#include "irrlicht.h"

using namespace irr;

class Plane
{
public:
    // Constructor
    Plane(irr::scene::ISceneManager*, irr::scene::ISceneNode *parentRotationNode, irr::io::path meshPath);
    // Destructor
    ~Plane(){}

    // Setters and getters
    void setScale(const irr::core::vector3df& scale){this->scale = scale; }
    const irr::core::vector3df& getScale() const {return this->scale; }

    void setNode(irr::scene::IAnimatedMeshSceneNode* node){this->node = node; }
    irr::scene::IAnimatedMeshSceneNode* getNode() const {return this->node; }

    // To initialize mesh and node
    int initialize();
    // To initialize the camera attached to

private:
    irr::scene::ISceneManager* smgr;
    irr::io::path meshPath;
    irr::scene::ISceneNode *parentRotationNode;

    irr::core::vector3df scale;

    irr::scene::IAnimatedMeshSceneNode* node;

};

#endif
