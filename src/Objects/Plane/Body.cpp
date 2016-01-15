#include "Body.hpp"

#include "irrlicht.h"

#include "iostream"

namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

Body::Body(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    this->scale = ic::vector3df(0.05,0.05,0.05);
    this->position = ic::vector3df(0.0,0.0,0.0);
}

void Body::initialize()
{
    is::IMesh *planeMesh = this->smgr->getMesh(this->meshPath);
    this->node = this->smgr->addMeshSceneNode(planeMesh);
    this->node->setParent(this->parentRotationNode);
    this->node->setMaterialFlag(iv::EMF_LIGHTING,false);
    this->node->setScale(this->scale);
    this->node->setPosition(this->position);
}
