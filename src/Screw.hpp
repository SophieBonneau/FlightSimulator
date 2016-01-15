#pragma once

#ifndef SCREW
#define SCREW

#include "irrlicht.h"
#include "PlaneElement.hpp"

using namespace irr;

class Screw : public PlaneElement
{
public:
    // Constructor
    Screw(irr::scene::ISceneManager*, irr::scene::ISceneNode*, irr::io::path);
    // Destructor
    ~Screw(){}

    // Setters and getters
    void setRotationStep(const double rotationStep){this->rotationStep = rotationStep; }
    double getRotationStep() const {return this->rotationStep; }

    // To initialize mesh and node
    void initialize();

    // To update the screw rotation while render
    int updateRotation();

private:
    irr::scene::IMesh* screw_mesh;
    irr::scene::IMeshSceneNode* screw_node;

    double rotationStep;

};

#endif
