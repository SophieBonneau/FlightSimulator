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
    void setScale(const irr::core::vector3df& scale){this->scale = scale; }
    const irr::core::vector3df& getScale() const {return this->scale; }

    void setNode(irr::scene::IMeshSceneNode* node){this->node = node; }
    irr::scene::IMeshSceneNode* getNode() const {return this->node; }

    void setMesh(irr::scene::IMesh* mesh){this->mesh = mesh; }
    irr::scene::IMesh* getMesh() const {return this->mesh; }

    // To initialize mesh and node
    void initialize();


private:
    irr::scene::ISceneManager* smgr;
    irr::io::path meshPath;

    irr::core::vector3df scale;

    irr::scene::IMeshSceneNode* node;
    irr::scene::IMesh* mesh;

};

#endif
