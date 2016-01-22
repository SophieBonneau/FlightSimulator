#pragma once

#ifndef LANDSCAPE
#define LANDSCAPE

#include "irrlicht.h"
#include "iostream"

/* Class Landscape: Class which manages the landscape objects
*/
class Landscape
{
public:
    /************************************************************************************/
    /******************************** Constructor **************************************/
    /************************************************************************************/
    /* Constructor Landscape: Initialize the global attributes: scale, mesh
     * params:   irr::scene::ISceneManager*: the application scene manager
     *           irr::io::path meshPath: the path to the map mesh
    */
    Landscape(irr::scene::ISceneManager*, irr::io::path);
    ~Landscape(){}

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* void setScale: set the mesh scale
     * params:  const irr::core::vector3df: the mesh scale
    */
    void setScale(const irr::core::vector3df& scale){   m_scale = scale; }

    /* irr::scene::IMeshSceneNode* getNode: get the scene node of the landscape for irrlicht purpose
     * return:  const irr::scene::IMeshSceneNode*: the landscape node
    */
    irr::scene::IMeshSceneNode* getNode() const     {   return m_node; }

    /* irr::scene::IMesh* getMesh: get the mesh of the landscape for irrlicht purpose
     * return:  const irr::scene::IMeshSceneNode*: the landscape mesh
    */
    irr::scene::IMesh* getMesh() const      {   return m_mesh; }

    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/
    /* void initialize:  Initialization of the landscape for the application node and mesh: size, position.
    */
    void initialize();

private:
    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/
    irr::scene::ISceneManager* m_smgr = nullptr;
    irr::io::path m_meshPath = "";

    irr::core::vector3df m_scale;

    irr::scene::IMeshSceneNode* m_node = nullptr;
    irr::scene::IMesh* m_mesh = nullptr;

};

#endif
