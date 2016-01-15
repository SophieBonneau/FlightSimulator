#include "Water.hpp"

#include "irrlicht.h"

#include "iostream"

namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Water::Water(is::ISceneManager* smgr, iv::ITexture * textureWater)
    :m_smgr(smgr), m_textureWater(textureWater)
{
    m_position =ic::vector3df(0,-2, 0);

    m_waveLength = 10.0f;
    m_waveSpeed = 500.0f;
    m_waveHeight = 0.2f;

    m_tileSize = ic::dimension2d<irr::f32>(4.6,4.6);
    m_tileCount = ic::dimension2d<irr::f32>(200,200);
    m_countHills = ic::dimension2d<irr::f32>(0,0);
    m_textureRepeatCount = ic::dimension2d<irr::f32>(5,5);
}

// To initialize mesh and node
void Water::initialize()
{
    is::IMesh *meshWater = m_smgr->addHillPlaneMesh( "myHill", m_tileSize, m_tileCount, 0, 0,m_countHills, m_textureRepeatCount);
    is::ISceneNode* planWater = m_smgr->addWaterSurfaceSceneNode(meshWater, m_waveHeight, m_waveSpeed, m_waveLength);
    planWater->setMaterialTexture(0, m_textureWater);
    planWater->setMaterialFlag(iv::EMF_LIGHTING, false);
    planWater->setMaterialType(iv::EMT_REFLECTION_2_LAYER);
    planWater->setPosition(m_position);
}
