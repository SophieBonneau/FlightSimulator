#pragma once

#ifndef TAIL
#define TAIL

#include "irrlicht.h"
#include "PlaneElement.hpp"

using namespace irr;

class Tail : public PlaneElement
{
public:
    // Constructor
    Tail(irr::scene::ISceneManager*, irr::scene::ISceneNode *parentRotationNode, irr::io::path meshPath);
    // Destructor
    ~Tail(){}

    // To initialize mesh and node
    void initialize();

private:

};

#endif
