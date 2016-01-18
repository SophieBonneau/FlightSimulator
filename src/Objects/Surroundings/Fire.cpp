#include "Fire.hpp"

#include "irrlicht.h"

#include "iostream"

namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

//Constructor
Fire::Fire(is::ISceneManager* smgr, iv::ITexture * textureFire)
    :m_smgr(smgr), m_textureFire(textureFire)
{
    m_scale = ic::vector3df(0.5,0.5,0.5);

    //Particules emitter
    m_size = ic::aabbox3d<irr::f32>(-7,0,-7,7,1,7);
    m_initDirection = ic::vector3df(0.0f,0.0f,0.0f);
    m_minRate = 800;
    m_maxRate = 1000;
    m_darkColor = iv::SColor(0,255,0,0);
    m_brightColor = iv::SColor(0,255,200,200);
    m_minAge = 500;
    m_maxAge = 800;
    m_angle = 0;
    m_minSize = ic::dimension2df(1.f,1.f);
    m_maxSize = ic::dimension2df(2.f,2.f);

}

// To initialize mesh and node
void Fire::initialize()
{
    ps = m_smgr->addParticleSystemSceneNode(false);
    em = ps->createBoxEmitter(m_size, m_initDirection, m_minRate, m_maxRate, m_darkColor, m_brightColor,
                                                    m_minAge, m_maxAge, m_angle, m_minSize, m_maxSize);
    is::IParticleAffector* paf = ps->createFadeOutParticleAffector();
    ps->addAffector(paf); // same goes for the affector
    paf->drop();
    ps->setScale(m_scale);
    ps->setMaterialTexture(0, m_textureFire);
    ps->setMaterialFlag(iv::EMF_LIGHTING, false);
    ps->setMaterialFlag(iv::EMF_ZWRITE_ENABLE, false);
    ps->setMaterialType(iv::EMT_TRANSPARENT_ADD_COLOR);
}
