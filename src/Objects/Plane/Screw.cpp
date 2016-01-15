#include "Screw.hpp"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Screw::Screw(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    this->smgr = smgr;
    this->parentRotationNode = parentRotationNode;
    this->meshPath = meshPath;

    this->scale = ic::vector3df(0.05,0.05,0.05);
    this->position = ic::vector3df(0.0,0.19,0.58);

    this->mesh = nullptr;

    this->rotationStep = 30.0f;

}

// To initialize water mesh and node
void Screw::initialize()
{
    this->mesh = this->smgr->getMesh(this->meshPath);
    this->node= this->smgr->addMeshSceneNode(this->mesh);
    this->node->setParent(this->parentRotationNode);
    this->node->setMaterialFlag(iv::EMF_LIGHTING,false);
    this->node->setScale(this->scale);
    this->node->setPosition(this->position);
}

int Screw::updateRotation()
{
    if(this->mesh == nullptr)
    {
        std::cout<<"Error: to update the rotation, you must have initialized the node first."<<std::endl;
        return -1;
    }

    ic::vector3df rotation_screw = this->node->getRotation();
    rotation_screw.Z += this->rotationStep;

    this->node->setRotation(rotation_screw);

    return 0;
}
