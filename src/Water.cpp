#include "Water.hpp"

#include "irrlicht.h"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Water::Water(is::ISceneManager* smgr, video::ITexture * textureWater)
    :smgr(smgr), textureWater(textureWater)
{
    this->position =ic::vector3df(0,-2, 0);

    this->waveLength = 10.0f;
    this->waveSpeed = 500.0f;
    this->waveHeight = 0.2f;

    this->tileSize = ic::dimension2d<f32>(4.6,4.6);
    this->tileCount = ic::dimension2d<u32>(200,200);
    this->countHills = ic::dimension2d<f32>(0,0);
    this->textureRepeatCount = ic::dimension2d<f32>(5,5);
}

// To initialize mesh and node
int Water::initialize()
{
    is::IMesh *mesh_water = this->smgr->addHillPlaneMesh( "myHill",
           this->tileSize,
           this->tileCount, 0, 0,
           this->countHills,
           this->textureRepeatCount);
    scene::ISceneNode* plan_water = smgr->addWaterSurfaceSceneNode(mesh_water, this->waveHeight, this->waveSpeed, this->waveLength);
    plan_water->setMaterialTexture(0, this->textureWater);
    plan_water->setMaterialFlag(iv::EMF_LIGHTING, false);
    plan_water->setMaterialType(video::EMT_REFLECTION_2_LAYER);
    plan_water->setPosition(this->position);

    return 0;
}
