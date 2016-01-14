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
    ~Screw();

    // Setters and getters
    void setScale(const irr::core::vector3df& scale);
    const irr::core::vector3df& getScale() const;

    void setPosition(const irr::core::vector3df& position);
    const irr::core::vector3df& getPosition() const;

    void setMeshPath(const irr::io::path& meshPath);
    const irr::io::path& getMeshPath() const;

    void setRotationStep(const double rotationStep);
    double getRotationStep() const;

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
