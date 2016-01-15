#pragma once

#ifndef WATER
#define WATER

#include "irrlicht.h"


class Water
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    /* Constructor Water: Initialize all global attributes of the classe: scale, mesh, size of waves
     * params:   irr::scene::ISceneManager*: the application scene manager
     *           irr::video::ITexture: the path to the water texture
    */
    Water(irr::scene::ISceneManager*, irr::video::ITexture *);
    ~Water(){}

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* void setPosition: set the water position on the application
     * return:  const irr::core::vector3df&: the position of the water mesh
    */
    void setPosition(const irr::core::vector3df& position){m_position = position;}

    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/
    /* void initialize:  Initialization of the water of the plane, node and mesh: size, position.
    */
    void initialize();


private:
    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/
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
