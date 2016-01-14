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

// Destructor
Water::~Water()
{

}

// Getters and setters
void Water::setPosition(const ic::vector3df& position)
{
    this->position = position;
}

void Water::setWaveHeight(const double waveHeight)
{
    this->waveHeight = waveHeight;
}

void Water::setWaveSpeed(const double waveSpeed)
{
    this->waveSpeed = waveSpeed;
}

void Water::setTileSize(const ic::dimension2d<f32>& tileSize)
{
    this->tileSize = tileSize;
}

void Water::setTileCount(const ic::dimension2d<u32>& tileCount)
{
    this->tileCount = tileCount;
}

void Water::setCountHills(const ic::dimension2d<f32>& countHills)
{
    this->countHills = countHills;
}

void Water::setTextureRepeatCount(const irr::core::dimension2d<f32>& textureRepeatCount)
{
    this->textureRepeatCount = textureRepeatCount;
}

double Water::getWaveLenght() const
{
    return this->waveLength;
}

double Water::getWaveHeight() const
{
    return this->waveHeight;
}

double Water::getWaveSpeed() const
{
    return this->waveSpeed;
}

const irr::core::dimension2d<f32>& Water::getTileSize() const
{
    return this->tileSize;
}

const irr::core::dimension2d<u32>& Water::getTileCount() const
{
    return this->tileCount;
}

const irr::core::dimension2d<f32>& Water::getCountHills() const
{
    return this->countHills;
}


const irr::core::dimension2d<f32>& Water::getTextureRepeatCount() const
{
    return this->textureRepeatCount;
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
