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
    ~Water(){}

    // Setters and getters
    void setPosition(const irr::core::vector3df& position){this->position = position;}
    irr::core::vector3df& getPosition() const;

    void setWaveLenght(const double waveLength){this->waveLength = waveLength;}
    double getWaveLenght() const {return this->waveLength;}

    void setWaveHeight(const double waveHeight){this->waveHeight = waveHeight;}
    double getWaveHeight() const {return this->waveLength;}

    void setWaveSpeed(const double waveSpeed){this->waveSpeed = waveSpeed;}
    double getWaveSpeed() const {return this->waveSpeed;}

    void setTileSize(const irr::core::dimension2d<f32>& tileSize){this->tileSize = tileSize;}
    const irr::core::dimension2d<f32>& getTileSize() const {return this->tileSize;}

    void setTileCount(const irr::core::dimension2d<u32>& tileCount){this->tileCount = tileCount;}
    const irr::core::dimension2d<u32>& getTileCount() const {return this->tileCount;}

    void setCountHills(const irr::core::dimension2d<f32>& countHills){this->countHills = countHills;}
    const irr::core::dimension2d<f32>& getCountHills() const {return this->countHills;}

    void setTextureRepeatCount(const irr::core::dimension2d<f32>& textureRepeatCount){this->textureRepeatCount = textureRepeatCount;}
    const irr::core::dimension2d<f32>& getTextureRepeatCount() const {return this->textureRepeatCount;}

    // To initialize mesh and node
    void initialize();


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
