#pragma once

#ifndef FIRE
#define FIRE

#include "irrlicht.h"


class Fire
{
public:
    // Constructor
    Fire(irr::scene::ISceneManager*, irr::video::ITexture *textureFire);
    // Destructor
    ~Fire(){}

    // Setters and getters
    void setPosition(const irr::core::vector3df& position){m_position = position;}
    irr::core::vector3df& getPosition() const;

    irr::scene::IParticleSystemSceneNode* getPs(){return ps;}
    irr::scene::IParticleEmitter* getEm(){return em;}

    // To initialize mesh and node
    void initialize();


private:
    irr::scene::ISceneManager* m_smgr;
    irr::video::ITexture *m_textureFire;
    irr::core::vector3df m_position;
    irr::core::vector3df m_scale;

    //Particules emitter
    irr::core::aabbox3d<irr::f32> m_size;       // emitter size
    irr::core::vector3df m_initDirection;  // initial direction
    int m_minRate;                         // Minimal amount of particles emitted per second
    int m_maxRate;                         // Maximal amount of particles emitted per second
    irr::video::SColor m_darkColor;        // darkest color
    irr::video::SColor m_brightColor;      // brightest color
    int m_minAge;                          // Minimal age
    int m_maxAge;                          // Maximal age
    float m_angle;                         // Angle
    irr::core::dimension2df m_minSize;     // Minimal size
    irr::core::dimension2df m_maxSize;     // Maximal size

    irr::scene::IParticleSystemSceneNode* ps;
    irr::scene::IParticleEmitter* em;
};

#endif
