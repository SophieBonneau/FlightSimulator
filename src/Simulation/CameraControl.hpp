#pragma once

#ifndef CAMERACONTROL
#define CAMERACONTROL

#include "irrlicht.h"

/* Class CameraControl: manages the position of the camera, according to the events launched by the EventReceiver class
*/
class CameraControl
{
public:
    /************************************************************************************/
    /******************************** Constructor **************************************/
    /************************************************************************************/
    /* Constructor CameraControl: Initialize the global attribute : the camera position
    */
    CameraControl(bool* keyIsDown);

    ~CameraControl(){}

    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/
    /* void changeCameraPose:  Change the position of the camera
     * params:  is::ICameraSceneNode *cameraNode:   Instance of the camera node
    */
    void changeCameraPose(irr::scene::ICameraSceneNode *cameraNode);

private:

    //Table to get the state of the keys
    bool* m_keyIsDown;

    //Coordinates of the camera
    irr::core::vector3df m_cameraPose;

};

#endif
