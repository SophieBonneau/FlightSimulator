#include "Screw.hpp"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

Screw::Screw(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    this->scale = ic::vector3df(0.05,0.05,0.05);
    this->position = ic::vector3df(0.0,0.19,0.58);
    this->screwMesh = nullptr;
    this->rotationStep = 30.0f;
}

void Screw::initialize()
{
    screwMesh = this->smgr->getMesh(this->meshPath);
    this->node= this->smgr->addMeshSceneNode(screwMesh);
    this->node->setParent(this->parentRotationNode);
    this->node->setMaterialFlag(iv::EMF_LIGHTING,false);
    this->node->setScale(this->scale);
    this->node->setPosition(this->position);
}

int Screw::updateRotation()
{
    if(this->screwMesh == nullptr)
    {
        std::cout<<"Error: To update the rotation, you must have initialized the node first."<<std::endl;
        return -1;
    }

    ic::vector3df rotation_screw = this->node->getRotation();
    rotation_screw.Z += this->rotationStep;

    this->node->setRotation(rotation_screw);

    return 0;
}
