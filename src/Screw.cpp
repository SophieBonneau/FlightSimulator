#include "Screw.hpp"

#include "irrlicht.h"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Screw::Screw(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath)
    :smgr(smgr), parentRotationNode(parentRotationNode), meshPath(meshPath)
{
    this->scale = ic::vector3df(0.05,0.05,0.05);
    this->position = ic::vector3df(0.0,0.19,0.58);

    this->screw_mesh = nullptr;
    this->screw_node = nullptr;

    this->rotationStep = 30.0f;

    this->parentRotationNode = parentRotationNode;

}

// Destructor
Screw::~Screw()
{

}

// Getters and setters
void Screw::setScale(const ic::vector3df& scale)
{
    this->scale = scale;
}

void Screw::setPosition(const ic::vector3df& position)
{
    this->position = position;
}

void Screw::setMeshPath(const irr::io::path& meshPath)
{
    this->meshPath = meshPath;
}

void Screw::setRotationStep(const double rotationStep)
{
    this->rotationStep = rotationStep;
}

const irr::core::vector3df& Screw::getScale() const
{
    return this->scale;
}

const irr::core::vector3df& Screw::getPosition() const
{
    return this->position;
}

const irr::io::path& Screw::getMeshPath() const
{
    return this->meshPath;
}

double Screw::getRotationStep() const
{
    return this->rotationStep;
}

// To initialize water mesh and node
int Screw::initialize()
{
    is::IMesh *mesh = smgr->getMesh(this->meshPath);
    this->screw_mesh = mesh;
    this->screw_node= smgr->addMeshSceneNode(screw_mesh);
    screw_node->setParent(this->parentRotationNode);
    screw_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    screw_node->setScale(this->scale);
    screw_node->setPosition(this->position);

    return 0;
}

int Screw::updateRotation()
{
    if(this->screw_mesh == nullptr)
    {
        std::cout<<"Error: to update the rotation, you must have initialized the node first."<<std::endl;
        return -1;
    }

    ic::vector3df rotation_screw = screw_node->getRotation();
    rotation_screw.Z += this->rotationStep;

    this->screw_node->setRotation(rotation_screw);

    return 0;
}
