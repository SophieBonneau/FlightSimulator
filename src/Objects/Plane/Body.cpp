#include "Body.hpp"

#include "irrlicht.h"

#include "iostream"

namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Body::Body(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    m_smgr = smgr;
    m_parentRotationNode = parentRotationNode;
    m_meshPath = meshPath;

    m_scale = ic::vector3df(0.05,0.05,0.05);
    m_position = ic::vector3df(0.0,0.0,0.0);
}

// To initialize mesh and node
void Body::initialize()
{
    is::IAnimatedMesh *plane_mesh = m_smgr->getMesh(m_meshPath);
    m_node = m_smgr->addMeshSceneNode(plane_mesh);
    m_node->setParent(m_parentRotationNode);
    m_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    m_node->setScale(m_scale);
    m_node->setPosition(m_position);
}
