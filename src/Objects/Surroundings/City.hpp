#pragma once

#ifndef CITY
#define CITY

#include "irrlicht.h"

using namespace irr;

class City
{
public:
    // Constructor
    City(irr::scene::ISceneManager*, irr::io::path meshPath);
    // Destructor
    ~City(){}

    // Setters and getters
    void setScale(const irr::core::vector3df& scale){m_scale = scale; }
    const irr::core::vector3df& getScale() const {return m_scale; }

    void setNode(irr::scene::IMeshSceneNode* node){m_node = node; }
    irr::scene::IMeshSceneNode* getNode() const {return m_node; }

    void setMesh(irr::scene::IMesh* mesh){m_mesh = mesh; }
    irr::scene::IMesh* getMesh() const {return m_mesh; }

    // To initialize mesh and node
    void initialize();


private:
    irr::scene::ISceneManager* m_smgr;
    irr::io::path m_meshPath;

    irr::core::vector3df m_scale;

    irr::scene::IMeshSceneNode* m_node;
    irr::scene::IMesh* m_mesh;

};

#endif
