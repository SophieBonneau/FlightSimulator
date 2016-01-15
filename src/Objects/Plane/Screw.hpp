#pragma once

#ifndef SCREW
#define SCREW

#include "irrlicht.h"
#include "PlaneElement.hpp"


class Screw : public PlaneElement
{
public:
    // Constructor
    Screw(irr::scene::ISceneManager*, irr::scene::ISceneNode*, irr::io::path);
    // Destructor
    ~Screw(){}

    // Setters and getters
    void setRotationStep(const double rotationStep){m_rotationStep = rotationStep; }
    double getRotationStep() const {return m_rotationStep; }

    // To initialize mesh and node
    void initialize();

    // To update the screw rotation while render
    int updateRotation();

private:
    double m_rotationStep;

};

#endif
