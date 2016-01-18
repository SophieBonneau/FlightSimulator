#include "Screw.hpp"

#include "iostream"

namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;
namespace io = irr::io;

Screw::Screw(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    m_scale = ic::vector3df(0.05,0.05,0.05);
    m_position = ic::vector3df(0.0,0.19,0.58);

    m_rotationStep = 30.0f;
}

int Screw::updateRotation()
{
    if(m_node == nullptr)
    {
        std::cout<<"Error: To update the rotation, you must have initialized the node first."<<std::endl;
        return -1;
    }

    ic::vector3df rotation_screw = m_node->getRotation();
    rotation_screw.Z += m_rotationStep;

    m_node->setRotation(rotation_screw);

    return 0;
}
