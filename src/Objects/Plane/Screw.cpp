#include "Screw.hpp"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Screw::Screw(is::ISceneManager* smgr, is::ISceneNode *parentRotationNode, irr::io::path meshPath):
    PlaneElement(smgr, parentRotationNode, meshPath)
{
    m_smgr = smgr;
    m_parentRotationNode = parentRotationNode;
    m_meshPath = meshPath;

    m_scale = ic::vector3df(0.05,0.05,0.05);
    m_position = ic::vector3df(0.0,0.19,0.58);

    m_mesh = nullptr;

    m_rotationStep = 30.0f;

}

// To initialize water mesh and node
void Screw::initialize()
{
    m_mesh = m_smgr->getMesh(m_meshPath);
    m_node= m_smgr->addMeshSceneNode(m_mesh);
    m_node->setParent(m_parentRotationNode);
    m_node->setMaterialFlag(iv::EMF_LIGHTING,false);
    m_node->setScale(m_scale);
    m_node->setPosition(m_position);
}

int Screw::updateRotation()
{
    if(m_mesh == nullptr)
    {
        std::cout<<"Error: to update the rotation, you must have initialized the node first."<<std::endl;
        return -1;
    }

    ic::vector3df rotation_screw = m_node->getRotation();
    rotation_screw.Z += m_rotationStep;

    m_node->setRotation(rotation_screw);

    return 0;
}
