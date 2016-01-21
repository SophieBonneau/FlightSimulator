#pragma once

#ifndef PLANEELEMENT
#define PLANEELEMENT

#include "irrlicht.h"


/* Class PlaneElement: Generic class which defines an element of the plane. Each of them
 * having the same behaviour, this class aims to ease the code.
*/
class PlaneElement
{
public:
    /************************************************************************************/
    /******************************** Constructor **************************************/
    /************************************************************************************/
    /* Constructor EventReceiver: Initialize all global attributes of the class
     * params:   irr::scene::ISceneManager* smgr: the application scene manager
                 irr::scene::ISceneNode *parentRotationNode: the general parent used for the global intern rotation of the plane
                 irr::io::path meshPath: the path to the specified plane element mesh
    */
    PlaneElement(irr::scene::ISceneManager* smgr,
                 irr::scene::ISceneNode *parentRotationNode,
                 irr::io::path meshPath)
        :m_smgr(smgr), m_parentRotationNode(parentRotationNode), m_meshPath(meshPath){}

    virtual ~PlaneElement(){}

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* void setScale: set the mesh scale
     * params:  const irr::core::vector3df: the mesh scale
    */
    void setScale(const irr::core::vector3df& scale){   m_scale = scale;    }

    /* void setPosition: set the mesh position in the application global referential
     * params:  const irr::core::vector3df &: the mesh position in the global referential
    */
    void setPosition(const irr::core::vector3df& position){ m_position = position; }

    /* irr::scene::IMeshSceneNode* getNode: get the specified object node for irrlicht purpose
     * return:  const irr::scene::IMeshSceneNode*: the current element node
    */
    irr::scene::IMeshSceneNode* getNode() const     {   return m_node;      }

    /************************************************************************************/
    /******************************** Public functions *********************************/
    /************************************************************************************/
    /* void initialize:  Initialization of the node and mesh
    */
    void initialize()
    {
        irr::scene::IMesh* mesh = m_smgr->getMesh(m_meshPath);
        m_node= m_smgr->addMeshSceneNode(mesh);
        m_node->setParent(m_parentRotationNode);
        m_node->setMaterialFlag(irr::video::EMF_LIGHTING,false);
        m_node->setScale(m_scale);
        m_node->setPosition(m_position);
    }

protected:
    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/
    irr::scene::ISceneManager* m_smgr = nullptr;
    irr::scene::ISceneNode *m_parentRotationNode = nullptr;
    irr::io::path m_meshPath = "";

    irr::core::vector3df m_scale = irr::core::vector3df(0.0, 0.0, 0.0);
    irr::core::vector3df m_position = irr::core::vector3df(0.0, 0.0, 0.0);

    irr::scene::IMeshSceneNode* m_node = nullptr;
};

#endif
