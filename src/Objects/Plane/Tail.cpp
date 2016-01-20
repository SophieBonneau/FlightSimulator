#include "Tail.hpp"

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

