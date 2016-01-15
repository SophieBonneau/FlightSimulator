#include "Tail.hpp"

#include "irrlicht.h"

#include "iostream"

namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;
namespace io = irr::io;


Tail::Tail(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    m_scale = ic::vector3df(0.05,0.05,0.05);
    m_position = ic::vector3df(0.0,0.0,0.0);
}

void Tail::initialize()
{
    is::IMesh *tail_mesh = m_smgr->getMesh(m_meshPath);
    m_node = m_smgr->addMeshSceneNode(tail_mesh);
    m_node->setParent(m_parentRotationNode);
    m_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    m_node->setScale(m_scale);
    m_node->setPosition(m_position);
}
