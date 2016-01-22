#pragma once

#ifndef FIRE
#define FIRE

#include "irrlicht.h"
#include "iostream"

/* Class Fire: Manage the fire objects characteristcs
*/
class Fire
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    /* Constructor Fire: Initialize the global attributes and the particule emmiter characteristics
     * params:   irr::scene::ISceneManager*: the application scene manager
                 irr::video::ITexture *: the fire particules texture
    */
    Fire(irr::scene::ISceneManager*, irr::video::ITexture *textureFire);

    ~Fire(){}

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/


    void setPosition(const irr::core::vector3df& position){m_position = position;}

    /* float getPosition: getter for the emitter box position
    * return:  irr::core::vector3df: the emitter box position
    */
    irr::core::vector3df& getPosition() const;

    /* float getPs: getter for the particule system node
    * return:  irr::scene::IParticleSystemSceneNode*: the particule system node
    */
    irr::scene::IParticleSystemSceneNode* getPs(){return ps;}

    /* float getEm: getter for the emitter box
    * return:  irr::scene::IParticleEmitter*: the particule emitter
    */
    irr::scene::IParticleEmitter* getEm(){return em;}

    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/
    /* void initialize: initialize the fire emitter box and the particle system
    */
    void initialize();


private:

    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/

    irr::scene::ISceneManager* m_smgr = nullptr;
    irr::video::ITexture *m_textureFire = nullptr;
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
