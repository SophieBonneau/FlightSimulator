#include "EventReceiver.hpp"
#include "irrlicht.h"
#include "iostream"

using namespace irr;
namespace ic = irr::core;
namespace is = irr::scene;

// Constructor
EventReceiver::EventReceiver()
{
    //Init keyboard states
    for(unsigned int i = 0; i<KEY_KEY_CODES_COUNT; ++i)
    {
        m_keyIsDown[i] = false;
    }

    //Init moving plane values
    m_planeWeight     = m_voidPlaneWeightKg;
    m_planeSpeed      = 0.0f;
    m_planeSpeedFloor = 0.0f;
    m_planeSpeedSlope = 0.0f;
    m_planeAltitude   = 0.0f;
    m_rotationAngle   = 0.0f;

    m_motorPower = 0.0f;

    m_isBrakes   = true;
    m_isStalling = false;
    m_isCrashed  = false;

    m_onFloor    = false;
    m_inTakeOff  = false;
    m_inFlight   = true;
    m_inLanding  = false;
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
    if(m_keyIsDown[KEY_KEY_P] == true)
        m_isBrakes = !m_isBrakes;

    if(!m_isBrakes)
    {
        ic::vector3df childRotation = node->getRotation();

        if(m_keyIsDown[KEY_UP] == true)
        {
            if(m_planeSpeed < m_maxPlaneSpeed)
            {
                m_planeSpeed += m_speedStep;
                m_planeSpeedFloor = m_planeSpeed;
            }
        }
        if(m_keyIsDown[KEY_DOWN] == true)
        {
            if(m_planeSpeed > m_minPlaneSpeed)
            {
                m_planeSpeed -= m_speedStep;
                m_planeSpeedFloor = m_planeSpeed;
            }
        }

        if(m_keyIsDown[KEY_KEY_Z] == true)
            childRotation.X -= m_altitudeAngleStep;
        if(m_keyIsDown[KEY_KEY_S] == true)
        {
            childRotation.X += m_altitudeAngleStep;
            if(childRotation.X >=2 )
            {
                m_onFloor = false;
                m_isCrashed = true;
            }
        }

        if(m_keyIsDown[KEY_KEY_D] == true)
            m_rotationAngle  += m_rotationAngleStep;
        if(m_keyIsDown[KEY_KEY_Q] == true)
            m_rotationAngle  -= m_rotationAngleStep;

        node->setRotation(childRotation);
    }
}

void EventReceiver::planeInTakeOff(is::ISceneNode *node)
{
    ic::vector3df childRotation = node->getRotation();

    if(m_keyIsDown[KEY_UP] == true)
    {
    }
    if(m_keyIsDown[KEY_DOWN] == true)
    {
    }

    if(m_keyIsDown[KEY_KEY_Z] == true)
    if(m_keyIsDown[KEY_KEY_S] == true)
    {
    }

    if(m_keyIsDown[KEY_KEY_D] == true)
    {
    }
    if(m_keyIsDown[KEY_KEY_Q] == true)
    {
    }
}

void EventReceiver::planeInFlight(is::ISceneNode *node,
                   is::IMeshSceneNode *leftwing_node, is::IMeshSceneNode *rightwing_node,
                   is::IMeshSceneNode *tail_node,
                   is::IMeshSceneNode *lefttail_node, is::IMeshSceneNode *righttail_node)
{
    if(m_stallSpeed < m_planeSpeed && m_stallSpeed * 1.1 > m_planeSpeed)
    {
    }
    if(m_stallSpeed >= m_planeSpeed)
    {
    }

    ic::vector3df childRotation     = node          ->getRotation();
    ic::vector3df leftwingRotation  = leftwing_node ->getRotation();
    ic::vector3df rightwingRotation = rightwing_node->getRotation();
    ic::vector3df tailRotation      = tail_node     ->getRotation();
    ic::vector3df lefttailRotation  = lefttail_node ->getRotation();
    ic::vector3df righttailRotation = righttail_node->getRotation();

    //Increase or decrease the plane speed
    if(m_keyIsDown[KEY_UP] == true)
    {
        if(m_motorPower < m_maxMotorPower)
            m_motorPower += m_motorStep;
    }
    if(m_keyIsDown[KEY_DOWN] == true)
    {
        if(m_motorPower > m_minMotorPower)
            m_motorPower -= m_motorStep;
    }

    //Get the plane up or down
    if(m_keyIsDown[KEY_KEY_Z] == true)
    {
        childRotation.X     -= m_altitudeAngleStep;
        lefttailRotation.X  -= 0.1;
        righttailRotation.X -= 0.1;
    }
    if(m_keyIsDown[KEY_KEY_S] == true)
    {
        childRotation.X     += m_altitudeAngleStep;
        lefttailRotation.X  += 0.1;
        righttailRotation.X += 0.1;
    }

    //Open the side panels of the plane to turn to the right or the left
    if(m_keyIsDown[KEY_KEY_D] == true)
    {
        //TD: Add the wind effect
        //If the plane is flat (not in the wrong inclinaison)
        if(childRotation.Z <= 0)
        {
            childRotation.Z     -= m_rotationAngleStep;
            leftwingRotation.X  -= 0.1;
            rightwingRotation.X += 0.1;
            tailRotation.Y      -= 0.1;
            tailRotation.Z      += 0.05;
        }
        else
        {
            childRotation.Z     -= 2 * m_rotationAngleStep;
            leftwingRotation.X  -= 2 * 0.1;
            rightwingRotation.X += 2 * 0.1;
            tailRotation.Y      -= 2 * 0.1;
            tailRotation.Z      += 2 * 0.05;
        }
    }
    if(m_keyIsDown[KEY_KEY_Q] == true)
    {
        if(childRotation.Z >= 0)
        {
            childRotation.Z     += m_rotationAngleStep;
            leftwingRotation.X  += 0.1;
            rightwingRotation.X -= 0.1;
            tailRotation.Y      += 0.1;
            tailRotation.Z      -= 0.05;
        }
        else
        {
            childRotation.Z     += 2 * m_rotationAngleStep;
            leftwingRotation.X  += 2 * 0.1;
            rightwingRotation.X -= 2* 0.1;
            tailRotation.Y      += 2 * 0.1;
            tailRotation.Z      -= 2 * 0.05;
        }
    }

    node->setRotation(childRotation);

    if(m_planeSpeed < m_motorPower)
        m_planeSpeed += 10/m_planeWeight * m_motorPower;
    else if(m_planeSpeed > m_motorPower)
        m_planeSpeed -= 10/m_planeWeight * m_motorPower;
    else
        m_planeSpeed  = m_motorPower;

    if(childRotation.X < 0)
        m_planeSpeedSlope = (1 + childRotation.X / 90) * m_planeSpeed;
    else if(childRotation.X == 0)
        m_planeSpeedSlope = m_planeSpeed;
    else if(childRotation.X > 0)
        m_planeSpeedSlope = (1 + childRotation.X / 90) * m_planeSpeed;

    m_planeSpeedFloor = cos(childRotation.X * core::DEGTORAD) * m_planeSpeedSlope;
    m_planeAltitude  -= sin(childRotation.X * core::DEGTORAD) * m_planeSpeedSlope;

    //Compute rotation
    float planeSpeedMByS = fromGameUnitToKt(m_planeSpeed) * 1.852 * 0.277777777778;
    if(planeSpeedMByS > 0)
        m_rotationAngle -= (tan(childRotation.Z * core::DEGTORAD) * m_g / planeSpeedMByS) * core::RADTODEG / 20; // for real values /80

    //Compute the stall speed
    m_loadFactor = (1/cos(-childRotation.Z*core::DEGTORAD));
    m_stallSpeed = sqrt(m_loadFactor) * m_flatStallSpeed;

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

    if(m_keyIsDown[KEY_UP] == true)
    {
    }
    if(m_keyIsDown[KEY_DOWN] == true)
    {
    }

    if(m_keyIsDown[KEY_KEY_Z] == true)
    if(m_keyIsDown[KEY_KEY_S] == true)
    {
    }

    if(m_keyIsDown[KEY_KEY_D] == true)
    {
    }
    if(m_keyIsDown[KEY_KEY_Q] == true)
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
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Z && !m_keyIsDown[KEY_KEY_Z]) // Go up
        {
            m_keyIsDown[KEY_KEY_Z] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Z && m_keyIsDown[KEY_KEY_Z])
        {
            m_keyIsDown[KEY_KEY_Z] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_S && !m_keyIsDown[KEY_KEY_S]) // Go down
        {
            m_keyIsDown[KEY_KEY_S] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_S)
        {
            m_keyIsDown[KEY_KEY_S] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Q && !m_keyIsDown[KEY_KEY_Q]) // Go left
        {
            m_keyIsDown[KEY_KEY_Q] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_Q) // Stop going left
        {
            m_keyIsDown[KEY_KEY_Q] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_D && !m_keyIsDown[KEY_KEY_D]) // Go right
        {
            m_keyIsDown[KEY_KEY_D] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_D) // Stop going right
        {
            m_keyIsDown[KEY_KEY_D] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_UP && !m_keyIsDown[KEY_UP]) // Higher engine speed
        {
            m_keyIsDown[KEY_UP] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_UP)
        {
            m_keyIsDown[KEY_UP] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_DOWN && !m_keyIsDown[KEY_DOWN]) // Lower engine speed
        {
            m_keyIsDown[KEY_DOWN] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_DOWN)
        {
            m_keyIsDown[KEY_DOWN] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_P && !m_keyIsDown[KEY_KEY_P]) // Unlock or lock brakes
        {
            m_keyIsDown[KEY_KEY_P] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_P)
        {
            m_keyIsDown[KEY_KEY_P] = false;
        }
    }
    return false;
}
