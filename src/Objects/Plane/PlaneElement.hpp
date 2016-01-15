#pragma once

#ifndef PLANEELEMENT
#define PLANEELEMENT

#include "irrlicht.h"

using namespace irr;

/* Class PlaneElement: Generic classe which is by each element of the plane. Each one of them
 * has the same kind of behaviour, permit to ease the code.
*/
class PlaneElement
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    /* Constructor EventReceiver: Initialize all global attributes of the classe
     * params:   irr::scene::ISceneManager* smgr: the application scene manager
                 irr::scene::ISceneNode *parentRotationNode: the general parent used for the global intern rotation of the plane
                 irr::io::path meshPath: the path to the specified plane element mesh
    */
    PlaneElement(irr::scene::ISceneManager* smgr,
                 irr::scene::ISceneNode *parentRotationNode,
                 irr::io::path meshPath)
        :smgr(smgr), parentRotationNode(parentRotationNode), meshPath(meshPath){}

    ~PlaneElement(){}

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* void setScale: set the mesh scale
     * params:  const irr::core::vector3df: the mesh scale
    */
    void setScale(const irr::core::vector3df& scale){   this->scale = scale;    }

    /* void setPosition: set the mesh position in the application global referential
     * params:  const irr::core::vector3df &: the mesh position in the global referential
    */
    void setPosition(const irr::core::vector3df& position){ this->position = position; }

    /* irr::scene::IMeshSceneNode* getNode: get the specified object node for irrlicht purpose
     * return:  const irr::scene::IMeshSceneNode*: the current element node
    */
    irr::scene::IMeshSceneNode* getNode() const     {   return this->node;      }


    /************************************************************************************/
    /******************************** Pubilic functions *********************************/
    /************************************************************************************/
    /* virtual void initialize:  Initialization of the node and mesh of the child classe.
    */
    virtual void initialize() = 0;

protected:
    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/
    irr::scene::ISceneManager* smgr;
    irr::scene::ISceneNode *parentRotationNode;
    irr::io::path meshPath;

    irr::core::vector3df scale;
    irr::core::vector3df position;

    irr::scene::IMeshSceneNode* node;
};

#endif
