#include "Body.hpp"

#include "irrlicht.h"

#include "iostream"

namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

Body::Body(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    m_scale = ic::vector3df(0.05,0.05,0.05);
    m_position = ic::vector3df(0.0,0.0,0.0);
}
