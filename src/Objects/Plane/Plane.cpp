#include "Plane.hpp"


namespace ic = irr::core;
namespace is = irr::scene;

Plane::Plane(is::ISceneManager* smgr)
    :m_smgr(smgr)
{
    //Init the object plane
    //2 parents: trajectory and rotation
    m_parentNode = m_smgr->addEmptySceneNode();
    m_parentNode->setPosition(ic::vector3df(-662.0, 0.0, -124.0));
    m_parentNode->setRotation(ic::vector3df(0.0, 30.0, 0.0));
    m_parentRotationNode = m_smgr->addEmptySceneNode();
    m_parentRotationNode->setParent(m_parentNode);

    //Init the plane
    m_body = new Body(m_smgr, m_parentRotationNode, "data/plane/plane.obj");
    m_body->initialize();

    //Init the screw
    m_screw = new Screw(m_smgr, m_parentRotationNode, "data/plane/screw.obj");
    m_screw->setPosition(ic::vector3df(0.0,0.19,0.58));
    m_screw->initialize();

    //Init the two wings
    m_leftWing = new Wing(m_smgr, m_parentRotationNode,"data/plane/leftWing.obj");
    m_leftWing->setPosition(ic::vector3df(-0.667,0.303,0.19));
    m_leftWing->initialize();
    m_rightWing = new Wing(m_smgr, m_parentRotationNode,"data/plane/rightWing.obj");
    m_rightWing->setPosition(ic::vector3df(0.667,0.303,0.19));
    m_rightWing->initialize();

    //Init the three tails
    m_middleTail = new Tail(m_smgr, m_parentRotationNode, "data/plane/tail.obj");
    m_middleTail->setPosition(ic::vector3df(0.001,0.355,-0.53));
    m_middleTail->initialize();
    m_leftTail = new Tail(m_smgr, m_parentRotationNode, "data/plane/leftTail.obj");
    m_leftTail->setPosition(ic::vector3df(-0.205,0.23,-0.441));
    m_leftTail->initialize();
    m_rightTail = new Tail(m_smgr, m_parentRotationNode, "data/plane/rightTail.obj");
    m_rightTail->setPosition(ic::vector3df(0.208,0.225,-0.441));
    m_rightTail->initialize();

    m_planeSpeed    = 0.0f;
    m_planeAltitude = 0.0f;
    m_rotAngle      = 0.0f;

}


void Plane::computeNewPosition(ic::vector3df rotation)
{
    ic::vector3df position = m_parentNode->getPosition();

    position.X += m_planeSpeed * sin(rotation.Y * M_PI / 180.0);
    position.Z += m_planeSpeed * cos(rotation.Y * M_PI / 180.0);
    position.Y = m_planeAltitude;

    m_parentNode->setRotation(rotation);
    m_parentNode->setPosition(position);
}
