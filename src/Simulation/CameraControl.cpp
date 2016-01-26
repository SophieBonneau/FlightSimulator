#include "CameraControl.hpp"

#include <iostream>

using namespace irr;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

CameraControl::CameraControl()
{
    //Init camera
    m_cameraPose = ic::vector3df(0.0,0.0,0.0);
}

void CameraControl::changeCameraPose(is::ICameraSceneNode *cameraNode)
{
    ic::vector3df cameraPosition = cameraNode->getPosition();

    if(m_keyIsDown[KEY_KEY_K] == true)
    {
        cameraPosition = ic::vector3df(0.0,5.0,-34.0);
        cameraNode->setPosition(cameraPosition);
    }
    else if(m_keyIsDown[KEY_KEY_L] == true)
    {
        cameraPosition = ic::vector3df(0.0,0.0,-0.1);
        cameraNode->setPosition(cameraPosition);
    }
    else if(m_keyIsDown[KEY_KEY_M] == true)
    {
        cameraPosition = ic::vector3df(0.0,18.0,-24.0);
        cameraNode->setPosition(cameraPosition);
    }
}
