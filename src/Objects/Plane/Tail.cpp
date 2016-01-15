#include "Tail.hpp"

#include "irrlicht.h"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

Tail::Tail(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    this->scale = ic::vector3df(0.05,0.05,0.05);
    this->position = ic::vector3df(0.0,0.0,0.0);
}

void Tail::initialize()
{
    is::IAnimatedMesh *tail_mesh = smgr->getMesh(this->meshPath);
    this->node = smgr->addMeshSceneNode(tail_mesh);
    this->node->setParent(this->parentRotationNode);
    this->node->setMaterialFlag(iv::EMF_LIGHTING,false);
    this->node->setScale(this->scale);
    this->node->setPosition(this->position);
}
