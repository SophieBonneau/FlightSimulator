#pragma once

#ifndef PLANEELEMENT
#define PLANEELEMENT

#include "irrlicht.h"


class PlaneElement
{
public:
    // Constructor
    PlaneElement(irr::scene::ISceneManager* smgr,
                 irr::scene::ISceneNode *parentRotationNode,
                 irr::io::path meshPath)
        :m_smgr(smgr), m_parentRotationNode(parentRotationNode), m_meshPath(meshPath){}

    // Destructor
    ~PlaneElement(){}

    // Setters and getters
    void setScale(const irr::core::vector3df& scale){m_scale = scale; }
    const irr::core::vector3df& getScale() const {return m_scale; }

    void setNode(irr::scene::IMeshSceneNode* node){m_node = node; }
    irr::scene::IMeshSceneNode* getNode() const {return m_node; }

    void setPosition(const irr::core::vector3df& position){m_position = position; }
    const irr::core::vector3df& getPosition() const {return m_position; }

    // To initialize mesh and node
    virtual void initialize() = 0;

protected:
    irr::scene::ISceneManager* m_smgr;
    irr::io::path m_meshPath;
    irr::scene::ISceneNode *m_parentRotationNode;

    irr::core::vector3df m_scale = irr::core::vector3df(0.0, 0.0, 0.0);
    irr::core::vector3df m_position = irr::core::vector3df(0.0, 0.0, 0.0);

    irr::scene::IMeshSceneNode* m_node = nullptr;
};

#endif
