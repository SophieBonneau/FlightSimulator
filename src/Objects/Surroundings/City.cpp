#include "City.hpp"

#include "irrlicht.h"

#include "iostream"

namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
City::City(is::ISceneManager* smgr, irr::io::path meshPath)
    :m_smgr(smgr), m_meshPath(meshPath)
{
    m_scale = ic::vector3df(10,10,10);
}

// To initialize mesh and node
void City::initialize()
{
    m_mesh = m_smgr->getMesh(m_meshPath);
    m_node = m_smgr->addOctreeSceneNode(m_mesh,nullptr,-1,1024);
    m_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    m_node->setScale(m_scale);
}
