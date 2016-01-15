#pragma once

#ifndef WATER
#define WATER

#include "irrlicht.h"


class Water
{
public:
    // Constructor
    Water(irr::scene::ISceneManager*, irr::video::ITexture *);
    // Destructor
    ~Water(){}

    // Setters and getters
    void setPosition(const irr::core::vector3df& position){m_position = position;}
    irr::core::vector3df& getPosition() const;

    void setWaveLenght(const double waveLength){m_waveLength = waveLength;}
    double getWaveLenght() const {return m_waveLength;}

    void setWaveHeight(const double waveHeight){m_waveHeight = waveHeight;}
    double getWaveHeight() const {return m_waveLength;}

    void setWavgeSpeed(const double waveSpeed){m_waveSpeed = waveSpeed;}
    double getWaveSpeed() const {return m_waveSpeed;}

    void setTileSize(const irr::core::dimension2d<irr::f32>& tileSize){m_tileSize = tileSize;}
    const irr::core::dimension2d<irr::f32>& getTileSize() const {return m_tileSize;}

    void setTileCount(const irr::core::dimension2d<irr::u32>& tileCount){m_tileCount = tileCount;}
    const irr::core::dimension2d<irr::u32>& getTileCount() const {return m_tileCount;}

    void setCountHills(const irr::core::dimension2d<irr::f32>& countHills){m_countHills = countHills;}
    const irr::core::dimension2d<irr::f32>& getCountHills() const {return m_countHills;}

    void setTextureRepeatCount(const irr::core::dimension2d<irr::f32>& textureRepeatCount){m_textureRepeatCount = textureRepeatCount;}
    const irr::core::dimension2d<irr::f32>& getTextureRepeatCount() const {return m_textureRepeatCount;}

    // To initialize mesh and node
    void initialize();


private:
    irr::scene::ISceneManager* m_smgr;
    irr::video::ITexture *m_textureWater;

    irr::core::vector3df m_position;
    double m_waveLength;
    double m_waveSpeed;
    double m_waveHeight;
    irr::core::dimension2d<irr::f32> m_tileSize;
    irr::core::dimension2d<irr::u32> m_tileCount;
    irr::core::dimension2d<irr::f32> m_countHills;
    irr::core::dimension2d<irr::f32> m_textureRepeatCount;

};

#endif
