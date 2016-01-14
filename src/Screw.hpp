#pragma once

#ifndef SCREW
#define SCREW

#include "irrlicht.h"

#include <string>

using namespace irr;

class Screw
{
public:
    // Constructor
    Screw(irr::scene::ISceneManager*, irr::scene::ISceneNode*, irr::io::path);
    // Destructor
    ~Screw(){}

    // Setters and getters
    void setScale(const irr::core::vector3df& scale){this->scale = scale; }
    const irr::core::vector3df& getScale() const {return this->scale; }

    void setPosition(const irr::core::vector3df& position){this->position = position; }
    const irr::core::vector3df& getPosition() const {return this->position; }

    void setMeshPath(const irr::io::path& meshPath){this->meshPath = meshPath; }
    const irr::io::path& getMeshPath() const{return this->meshPath; }

    void setRotationStep(const double rotationStep){this->rotationStep = rotationStep; }
    double getRotationStep() const {return this->rotationStep; }

    // To initialize mesh and node
    int initialize();
    // To update the screw rotation while render
    int updateRotation();

private:
    irr::scene::ISceneManager* smgr;
    irr::scene::ISceneNode *parentRotationNode;

    irr::scene::IMesh* screw_mesh;
    irr::scene::IMeshSceneNode* screw_node;

    irr::core::vector3df scale;
    irr::core::vector3df position;
    irr::io::path meshPath;

    double rotationStep;

};

#endif
