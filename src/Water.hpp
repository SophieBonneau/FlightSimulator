#pragma once

#ifndef WATER
#define WATER

#include "irrlicht.h"

using namespace irr;

class Water
{
public:
    // Constructor
    Water(irr::scene::ISceneManager*, video::ITexture *);
    // Destructor
    ~Water();

    // Setters and getters
    void setPosition(const irr::core::vector3df& position);
    irr::core::vector3df& getPosition() const;

    void setWaveLenght(const double waveLength);
    double getWaveLenght() const;

    void setWaveHeight(const double waveHeight);
    double getWaveHeight() const;

    void setWaveSpeed(const double waveSpeed);
    double getWaveSpeed() const;

    void setTileSize(const irr::core::dimension2d<f32>& tileSize);
    const irr::core::dimension2d<f32>& getTileSize() const;

    void setTileCount(const irr::core::dimension2d<u32>& tileCount);
    const irr::core::dimension2d<u32>& getTileCount() const;

    void setCountHills(const irr::core::dimension2d<f32>& countHills);
    const irr::core::dimension2d<f32>& getCountHills() const;

    void setTextureRepeatCount(const irr::core::dimension2d<f32>& textureRepeatCount);
    const irr::core::dimension2d<f32>& getTextureRepeatCount() const;

    // To initialize mesh and node
    int initialize();


private:
    irr::scene::ISceneManager* smgr;
    video::ITexture *textureWater;

    irr::core::vector3df position;
    double waveLength;
    double waveSpeed;
    double waveHeight;
    irr::core::dimension2d<f32> tileSize;
    core::dimension2d<u32> tileCount;
    core::dimension2d<f32> countHills;
    core::dimension2d<f32> textureRepeatCount;

};

#endif
