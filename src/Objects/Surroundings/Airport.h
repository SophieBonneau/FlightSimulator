#pragma once

#ifndef AIRPORT_H
#define AIRPORT_H

#include "irrlicht.h"

class Airport
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    /* Constructor City: Initialize all global attributes of the classe: scale, mesh
     * params:   irr::scene::ISceneManager*: the application scene manager
     *           irr::io::path meshPath: the path to the map mesh
    */
    Airport(irr::scene::ISceneManager*, irr::io::path);
    ~Airport(){}

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* void setScale: set the mesh scale
     * params:  const irr::core::vector3df: the mesh scale
    */
    void setScale(const irr::core::vector3df& scale){   m_scale = scale; }

    /* irr::scene::IMeshSceneNode* getNode: get the scene node of the airport for irrlicht purpose
     * return:  const irr::scene::IMeshSceneNode*: the landscape node
    */
    irr::scene::IMeshSceneNode* getNode() const     {   return m_node; }

    /* irr::scene::IMesh* getMesh: get the airport mesh of the airport for irrlicht purpose
     * return:  const irr::scene::IMeshSceneNode*: the airport mesh
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
    irr::scene::ISceneManager* m_smgr;
    irr::io::path m_meshPath;

    irr::core::vector3df m_scale;

    irr::scene::IMeshSceneNode* m_node;
    irr::scene::IMesh* m_mesh;
};

#endif // AIRPORT_H
