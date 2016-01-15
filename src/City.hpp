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

    // To initialize mesh and node
    void initialize();


private:
    irr::scene::ISceneManager* smgr;
    irr::io::path meshPath;

    irr::core::vector3df scale;

};

#endif
