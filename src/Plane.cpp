#include "Plane.hpp"

#include "irrlicht.h"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Plane::Plane(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath)
    :smgr(smgr), meshPath(meshPath), parentRotationNode(parentRotationNode)
{
    ic::vector3df(0.05,0.05,0.05);
}

// To initialize mesh and node
int Plane::initialize()
{
    is::IAnimatedMesh *plane_mesh = smgr->getMesh(this->meshPath);
    is::IAnimatedMeshSceneNode *plane_node= smgr->addAnimatedMeshSceneNode(plane_mesh);
    plane_node->setParent(this->parentRotationNode);
    plane_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    plane_node->setScale(this->scale);

    return 0;
}
