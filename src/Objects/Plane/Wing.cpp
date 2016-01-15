#include "Wing.hpp"

#include "irrlicht.h"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Wing::Wing(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    this->scale = ic::vector3df(0.05,0.05,0.05);
    this->position = ic::vector3df(0.0,0.0,0.0);
}

// To initialize mesh and node
void Wing::initialize()
{
    is::IAnimatedMesh *wing_mesh = smgr->getMesh(meshPath);
    is::IAnimatedMeshSceneNode *wing_node = smgr->addAnimatedMeshSceneNode(wing_mesh);
    wing_node->setParent(parentRotationNode);
    wing_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    wing_node->setScale(this->scale);
    wing_node->setPosition(this->position);
}
