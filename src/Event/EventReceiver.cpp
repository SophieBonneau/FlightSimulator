#include "EventReceiver.hpp"

#include "irrlicht.h"

#include "iostream"

using namespace irr;
namespace ig = irr::gui;
namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;

// Constructor
EventReceiver::EventReceiver()
{
    //Init keyboard states
    for(unsigned int i = 0; i<KEY_KEY_CODES_COUNT; ++i)
    {
        this->keyIsDown[i] = false;
    }

    //Init moving plane values
    this->planeWeight     = voidPlaneWeightKg;
    this->planeSpeed      = 0.0f;
    this->planeSpeedFloor = 0.0f;
    this->planeSpeedSlope       = 0.0f;
    this->planeAltitude   = 0.0f;
    this->rotationAngle   = 0.0f;

    this->motorPower = 0.0f;

    this->isBrakes   = true;
    this->isStalling = false;
    this->isCrashed  = false;

    this->onFloor    = false;
    this->inTakeOff  = false;
    this->inFlight   = true;
    this->inLanding  = false;
}

float EventReceiver::fromKtToGameUnit(float valueToConvert)
{
    return valueToConvert / 400.0f;
}

float EventReceiver::fromGameUnitToKt(float valueToConvert)
{
    return valueToConvert * 400.0f;
}

void EventReceiver::planeOnFloor(is::ISceneNode *node)
{
    //Brakes used only on the plane wheels
    if(keyIsDown[KEY_KEY_P] == true)
        isBrakes = !isBrakes;

    if(!isBrakes)
    {
        ic::vector3df childRotation = node->getRotation();

        if(keyIsDown[KEY_UP] == true)
        {
            if(planeSpeed < maxPlaneSpeed)
            {
                planeSpeed += speedStep;
                planeSpeedFloor = planeSpeed;
            }
        }
        if(keyIsDown[KEY_DOWN] == true)
        {
            if(planeSpeed > minPlaneSpeed)
            {
                planeSpeed -= speedStep;
                planeSpeedFloor = planeSpeed;
            }
        }

        if(keyIsDown[KEY_KEY_Z] == true)
            childRotation.X -= altitudeAngleStep;
        if(keyIsDown[KEY_KEY_S] == true)
        {
            childRotation.X += altitudeAngleStep;
            if(childRotation.X >=2 )
            {
                onFloor = false;
                isCrashed = true;
            }
        }

        if(keyIsDown[KEY_KEY_D] == true)
            rotationAngle  += rotationAngleStep;
        if(keyIsDown[KEY_KEY_Q] == true)
            rotationAngle  -= rotationAngleStep;

        node->setRotation(childRotation);
    }
}

void EventReceiver::planeInTakeOff(is::ISceneNode *node)
{
    ic::vector3df childRotation = node->getRotation();

    if(keyIsDown[KEY_UP] == true)
    {
    }
    if(keyIsDown[KEY_DOWN] == true)
    {
    }

    if(keyIsDown[KEY_KEY_Z] == true)
    if(keyIsDown[KEY_KEY_S] == true)
    {
    }

    if(keyIsDown[KEY_KEY_D] == true)
    {
    }
    if(keyIsDown[KEY_KEY_Q] == true)
    {
    }
}

void EventReceiver::planeInFlight(is::ISceneNode *node,
                   is::IMeshSceneNode *leftwing_node, is::IMeshSceneNode *rightwing_node,
                   is::IMeshSceneNode *tail_node,
                   is::IMeshSceneNode *lefttail_node, is::IMeshSceneNode *righttail_node)
{
    if(stallSpeed < planeSpeed && stallSpeed * 1.1 > planeSpeed)
    {
    }
    if(stallSpeed >= planeSpeed)
    {
    }

    ic::vector3df childRotation     = node          ->getRotation();
    ic::vector3df leftwingRotation  = leftwing_node ->getRotation();
    ic::vector3df rightwingRotation = rightwing_node->getRotation();
    ic::vector3df tailRotation      = tail_node     ->getRotation();
    ic::vector3df lefttailRotation  = lefttail_node ->getRotation();
    ic::vector3df righttailRotation = righttail_node->getRotation();

    //Increase or decrease the plane speed
    if(keyIsDown[KEY_UP] == true)
    {
        if(motorPower < maxMotorPower)
            motorPower += motorStep;
    }
    if(keyIsDown[KEY_DOWN] == true)
    {
        if(motorPower > minMotorPower)
            motorPower -= motorStep;
    }

    //Get the plane up or down
    if(keyIsDown[KEY_KEY_Z] == true)
    {
        childRotation.X     -= altitudeAngleStep;
        lefttailRotation.X  -= 0.1;
        righttailRotation.X -= 0.1;
    }
    if(keyIsDown[KEY_KEY_S] == true)
    {
        childRotation.X     += altitudeAngleStep;
        lefttailRotation.X  += 0.1;
        righttailRotation.X += 0.1;
    }

    //Open the side panels of the plane to turn to the right or the left
    if(keyIsDown[KEY_KEY_D] == true)
    {
        //TD: Add the wind effect
        //If the plane is flat (not in the wrong inclinaison)
        if(childRotation.Z <= 0)
        {
            childRotation.Z     -= rotationAngleStep;
            leftwingRotation.X  -= 0.1;
            rightwingRotation.X += 0.1;
            tailRotation.Y      -= 0.1;
            tailRotation.Z      += 0.05;
        }
        else
        {
            childRotation.Z     -= 2 * rotationAngleStep;
            leftwingRotation.X  -= 2 * 0.1;
            rightwingRotation.X += 2 * 0.1;
            tailRotation.Y      -= 2 * 0.1;
            tailRotation.Z      += 2 * 0.05;
        }
    }
    if(keyIsDown[KEY_KEY_Q] == true)
    {
        if(childRotation.Z >= 0)
        {
            childRotation.Z     += rotationAngleStep;
            leftwingRotation.X  += 0.1;
            rightwingRotation.X -= 0.1;
            tailRotation.Y      += 0.1;
            tailRotation.Z      -= 0.05;
        }
        else
        {
            childRotation.Z     += 2 * rotationAngleStep;
            leftwingRotation.X  += 2 * 0.1;
            rightwingRotation.X -= 2* 0.1;
            tailRotation.Y      += 2 * 0.1;
            tailRotation.Z      -= 2 * 0.05;
        }
    }

    node->setRotation(childRotation);

    if(planeSpeed < motorPower)
        planeSpeed += 1/planeWeight * motorPower;
    if(planeSpeed > motorPower)
        planeSpeed -= 1/planeWeight * motorPower;

    if(planeSpeed < motorPower)
        planeSpeed += 10/planeWeight * motorPower;
    else if(planeSpeed > motorPower)
        planeSpeed -= 10/planeWeight * motorPower;
    else
        planeSpeed  = motorPower;

    if(childRotation.X < 0)
        planeSpeedSlope = (1 + childRotation.X / 90) * planeSpeed;
    else if(childRotation.X == 0)
        planeSpeedSlope = planeSpeed;
    else if(childRotation.X > 0)
        planeSpeedSlope = (1 + childRotation.X / 90) * planeSpeed;

    planeSpeedFloor = cos(childRotation.X * core::DEGTORAD) * planeSpeedSlope;
    planeAltitude  -= sin(childRotation.X * core::DEGTORAD) * planeSpeedSlope;

    //Compute rotation
    float planeSpeedMByS = fromGameUnitToKt(planeSpeed) * 1.852 * 0.277777777778;
    if(planeSpeedMByS > 0)
        rotationAngle -= (tan(childRotation.Z * core::DEGTORAD) * g / planeSpeedMByS) * core::RADTODEG / 20; // for real values /80

    //Compute the stall speed
    loadFactor = (1/cos(-childRotation.Z*core::DEGTORAD));
    stallSpeed = sqrt(loadFactor) * flatStallSpeed;

    node            ->setRotation(childRotation);
    leftwing_node   ->setRotation(leftwingRotation);
    rightwing_node  ->setRotation(rightwingRotation);
    tail_node       ->setRotation(tailRotation);
    lefttail_node   ->setRotation(lefttailRotation);
    righttail_node  ->setRotation(righttailRotation);
}

void EventReceiver::planeInLanding(is::ISceneNode *node)
{
    ic::vector3df childRotation = node->getRotation();

    if(keyIsDown[KEY_UP] == true)
    {
    }
    if(keyIsDown[KEY_DOWN] == true)
    {
    }

    if(keyIsDown[KEY_KEY_Z] == true)
    if(keyIsDown[KEY_KEY_S] == true)
    {
    }

    if(keyIsDown[KEY_KEY_D] == true)
    {
    }
    if(keyIsDown[KEY_KEY_Q] == true)
    {
    }
}

bool EventReceiver::OnEvent(const SEvent &event)
{
    if (event.EventType == EET_KEY_INPUT_EVENT)
    {
        if(event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.Key == KEY_ESCAPE)
        {
            exit(0);
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Z && !keyIsDown[KEY_KEY_Z]) // Go up
        {
            keyIsDown[KEY_KEY_Z] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Z && keyIsDown[KEY_KEY_Z])
        {
            keyIsDown[KEY_KEY_Z] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_S && !keyIsDown[KEY_KEY_S]) // Go down
        {
            keyIsDown[KEY_KEY_S] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_S)
        {
            keyIsDown[KEY_KEY_S] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Q && !keyIsDown[KEY_KEY_Q]) // Go left
        {
            keyIsDown[KEY_KEY_Q] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Q) // Stop going left
        {
            keyIsDown[KEY_KEY_Q] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_D && !keyIsDown[KEY_KEY_D]) // Go right
        {
            keyIsDown[KEY_KEY_D] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_D) // Stop going right
        {
            keyIsDown[KEY_KEY_D] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_UP && !keyIsDown[KEY_UP]) // Higher engine speed
        {
            keyIsDown[KEY_UP] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_UP)
        {
            keyIsDown[KEY_UP] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_DOWN && !keyIsDown[KEY_DOWN]) // Lower engine speed
        {
            keyIsDown[KEY_DOWN] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_DOWN)
        {
            keyIsDown[KEY_DOWN] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_P && !keyIsDown[KEY_KEY_P]) // Unlock or lock brakes
        {
            keyIsDown[KEY_KEY_P] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_P)
        {
            keyIsDown[KEY_KEY_P] = false;
        }
    }
    return false;
}
