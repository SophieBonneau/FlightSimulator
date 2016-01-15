#include "Body.hpp"

#include "irrlicht.h"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Body::Body(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    this->smgr = smgr;
    this->parentRotationNode = parentRotationNode;
    this->meshPath = meshPath;

    this->scale = ic::vector3df(0.05,0.05,0.05);
}

// To initialize mesh and node
void Body::initialize()
{
    is::IAnimatedMesh *plane_mesh = this->smgr->getMesh(this->meshPath);
    this->node = this->smgr->addAnimatedMeshSceneNode(plane_mesh);
    this->node->setParent(this->parentRotationNode);
    this->node->setMaterialFlag(iv::EMF_LIGHTING,false);
    this->node->setScale(this->scale);
}
