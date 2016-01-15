#pragma once

#ifndef PLANEELEMENT
#define PLANEELEMENT

#include "irrlicht.h"

using namespace irr;

class PlaneElement
{
public:
    // Constructor
    PlaneElement(irr::scene::ISceneManager* smgr,
                 irr::scene::ISceneNode *parentRotationNode,
                 irr::io::path meshPath)
        :smgr(smgr), parentRotationNode(parentRotationNode), meshPath(meshPath){}

    // Destructor
    ~PlaneElement(){}

    // Setters and getters
    void setScale(const irr::core::vector3df& scale){this->scale = scale; }
    const irr::core::vector3df& getScale() const {return this->scale; }

    void setNode(irr::scene::IMeshSceneNode* node){this->node = node; }
    irr::scene::IMeshSceneNode* getNode() const {return this->node; }

    void setPosition(const irr::core::vector3df& position){this->position = position; }
    const irr::core::vector3df& getPosition() const {return this->position; }

    // To initialize mesh and node
    virtual void initialize() = 0;

protected:
    irr::scene::ISceneManager* smgr;
    irr::io::path meshPath;
    irr::scene::ISceneNode *parentRotationNode;

    irr::core::vector3df scale;
    irr::core::vector3df position;

    irr::scene::IMeshSceneNode* node;
};

#endif
