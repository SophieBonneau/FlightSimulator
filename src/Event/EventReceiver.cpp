#include "EventReceiver.hpp"
#include "irrlicht.h"
#include "iostream"

using namespace irr;
namespace ic = irr::core;
namespace is = irr::scene;
namespace ig = irr::gui;

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
    m_planeAltitude   = 8.7f;
    m_rotationAngle   = 0.0f;
    m_rotationAltitude = 0.0f;

    m_motorPower = 0.0f;
    m_fuelLiter = 152.0f;

    m_isBrakes   = true;
    m_isAlmostStalling = false;
    m_isStalling = false;
    m_isCrashed  = false;

    m_onFloor    = true;
    m_inTakeOff  = false;
    m_inFlight   = false;
    m_inLanding  = false;

    m_cameraPose = ic::vector3df(0.0,0.0,0.0);
}

float EventReceiver::fromKtToGameUnit(float valueToConvert)
{
    return valueToConvert / 400.0f;
}

float EventReceiver::fromGameUnitToKt(float valueToConvert)
{
    return valueToConvert * 400.0f;
}

float EventReceiver::fromKtToKmH(float valueToConvert)
{
    return valueToConvert * 1.852;
}

float EventReceiver::fromGameUnitToM(float valueToConvert)
{
    return valueToConvert * 4;
}

float EventReceiver::fromKmToMS(float valueToConvert)
{
    return valueToConvert * 0.277778;
}

void EventReceiver::computeTemperatureFromTheAltitude()
{
    float currentAltitude = fromGameUnitToM(m_planeAltitude);
    m_currentTemperature = ((m_tempAt0YInK - m_tempAt3000YInK)/(0 - 3000)) * currentAltitude
            + ((0 * m_tempAt0YInK - 3000 * m_tempAt0YInK)/(0 - 3000));

    std::cout<<"temperature: "<<m_currentTemperature<<std::endl;
}

void EventReceiver::computeAirDensity()
{
    float hs = (m_raynoldsNumber * m_currentTemperature) / (m_airMolarMasse * m_g);

    std::cout<<"hs: "<<std::endl;
    m_currentDensity = m_densityAt0 * exp(-fromGameUnitToM(m_planeAltitude)/hs);

    std::cout<<"density: "<<m_currentDensity<<std::endl;
}

void EventReceiver::computeLiftForce(float rotAngle)
{
    float cz = - 2 * M_PI * rotAngle;
    float speed = fromGameUnitToKt(fromKmToMS(m_planeSpeed));
    m_liftForce = 0.5 * m_currentDensity * m_sizeWings * cz * speed;
    std::cout<<"Lift Force: "<<m_liftForce<<std::endl;
}

void EventReceiver::planeOnFloor(is::ISceneNode *node)
{
    ic::vector3df childRotation = node->getRotation();

    computeTemperatureFromTheAltitude();
    computeAirDensity();
    computeLiftForce(childRotation.X);
    std::cout<<"Weight force : "<<m_weightForce<<std::endl;

    if(m_keyIsDown[KEY_UP] == true)
    {
        if(m_motorPower < m_maxMotorPower)
            m_motorPower += m_motorStep;
    }
    if(m_keyIsDown[KEY_DOWN] == true)
    {
        if(m_motorPower > m_minMotorPower)
            m_motorPower -= m_motorStep;
        else
            m_motorPower = m_minMotorPower;
    }

    //Get the plane up or down
    if(m_keyIsDown[KEY_KEY_Z] == true && !m_isBrakes)
    {
        if(fromGameUnitToKt(m_planeSpeedFloor) >= 60)
        {
            m_onFloor   = false;
            m_inTakeOff = true;
        }
        childRotation.X = 10 * m_altitudeAngleStep;
    }
    if(m_keyIsDown[KEY_KEY_S] == true && !m_isBrakes)
    {
        if(fromGameUnitToKt(m_planeSpeedFloor) >= 25)
        {
            m_onFloor   = false;
            m_isCrashed = true;
        }
    }

    float currentRotationAngle = 0.0f;
    //Open the side panels of the plane to turn to the right or the left
    if(m_keyIsDown[KEY_KEY_D] == true && !m_isBrakes)
    {
        if(fromGameUnitToKt(m_planeSpeedFloor) < 50)
            currentRotationAngle = 10 * m_rotationAngleStep;
        else
        {
            childRotation.Z     += 10 * m_rotationAngleStep;
            m_onFloor   = false;
            m_isCrashed = true;
        }
    }
    if(m_keyIsDown[KEY_KEY_Q] == true && !m_isBrakes)
    {
        if(fromGameUnitToKt(m_planeSpeedFloor) < 50)
            currentRotationAngle = -10 * m_rotationAngleStep;
        else
        {
            childRotation.Z     += 10 * m_rotationAngleStep;
            m_onFloor   = false;
            m_isCrashed = true;
        }
    }

    node->setRotation(childRotation);

    float planeSpeedMByS = fromKmToMS(fromKtToKmH(fromGameUnitToKt(m_planeSpeedFloor)));
    if(m_planeSpeedFloor > 0)
        m_rotationAngle += tan(currentRotationAngle * core::DEGTORAD) / planeSpeedMByS * core::RADTODEG;

    if(!m_isBrakes)
    {
        if(m_planeSpeedFloor < m_motorPower / 10.0)
            m_planeSpeedFloor += 0.2/m_planeWeight * m_motorPower;
        else if(m_planeSpeedFloor > m_motorPower / 10.0)
        {
            if(m_motorPower > m_minMotorPower)
                m_planeSpeedFloor -= 0.2/m_planeWeight * m_motorPower;
            else
                m_planeSpeedFloor -= 0.2/m_planeWeight;
        }
        else
            m_planeSpeedFloor  = m_motorPower;
        if(m_planeSpeedFloor < 0)
            m_planeSpeedFloor = 0;
        m_planeSpeed = m_planeSpeedFloor;
        m_fuelLiter -= m_motorPower / 200;
    }
}

void EventReceiver::planeInTakeOff(is::ISceneNode *node,
                                   is::IMeshSceneNode *leftwing_node, is::IMeshSceneNode *rightwing_node,
                                   is::IMeshSceneNode *tail_node,
                                   is::IMeshSceneNode *lefttail_node, is::IMeshSceneNode *righttail_node)
{
    ic::vector3df childRotation     = node          ->getRotation();
    ic::vector3df leftwingRotation  = leftwing_node ->getRotation();
    ic::vector3df rightwingRotation = rightwing_node->getRotation();
    ic::vector3df tailRotation      = tail_node     ->getRotation();
    ic::vector3df lefttailRotation  = lefttail_node ->getRotation();
    ic::vector3df righttailRotation = righttail_node->getRotation();

    computeTemperatureFromTheAltitude();
    computeAirDensity();
    computeLiftForce(childRotation.X);

    if(m_isStalling)
        m_planeAltitude -= m_stallStep;
    else
    {
        if(m_keyIsDown[KEY_DOWN] == true)
        {
            if(m_motorPower > m_minMotorPower)
                m_isStalling = true;
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
            if(childRotation.X < 3.0)
                m_isStalling = true;
            else
            {
                childRotation.X     += m_altitudeAngleStep;
                lefttailRotation.X  += 0.1;
                righttailRotation.X += 0.1;
            }
        }

        //Open the side panels of the plane to turn to the right or the left
        if(m_keyIsDown[KEY_KEY_D] == true)
        {
            if(childRotation.Z <= 0)
            {
                childRotation.Z     -= 40 * m_rotationAngleStep;
                leftwingRotation.X  -= 0.1;
                rightwingRotation.X += 0.1;
                tailRotation.Y      -= 0.1;
                tailRotation.Z      += 0.05;
                m_isStalling         = true;
            }
        }
        if(m_keyIsDown[KEY_KEY_Q] == true)
        {
            if(childRotation.Z >= 0)
            {
                childRotation.Z     += 40 * m_rotationAngleStep;
                leftwingRotation.X  += 0.1;
                rightwingRotation.X -= 0.1;
                tailRotation.Y      += 0.1;
                tailRotation.Z      -= 0.05;
                m_isStalling         = true;
            }
        }

        node->setRotation(childRotation);

        if(m_planeSpeed < m_motorPower / 10.0)
            m_planeSpeed += 0.2/m_planeWeight * m_motorPower;
        else if(m_planeSpeed > m_motorPower / 10.0)
            m_planeSpeed -= 0.2/m_planeWeight * m_motorPower;
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

        m_rotationAltitude = childRotation.X;

        if(m_planeSpeedFloor < m_flatStallSpeed)
        {
            m_isStalling = true;
        }
        if(m_planeAltitude > 9.0 + 15)
        {
            m_inTakeOff = false;
            m_inFlight  = true;
        }

        //Compute rotation
        float planeSpeedMByS = fromGameUnitToKt(m_planeSpeed) * 1.852 * 0.277777777778;
        if(planeSpeedMByS > 0)
            m_rotationAngle -= (tan(childRotation.Z * core::DEGTORAD) * m_g / planeSpeedMByS) * core::RADTODEG / 20; // for real values /80

        node            ->setRotation(childRotation);
        leftwing_node   ->setRotation(leftwingRotation);
        rightwing_node  ->setRotation(rightwingRotation);
        tail_node       ->setRotation(tailRotation);
        lefttail_node   ->setRotation(lefttailRotation);
        righttail_node  ->setRotation(righttailRotation);
    }
}

void EventReceiver::planeInFlight(is::ISceneNode *node,
                   is::IMeshSceneNode *leftwing_node, is::IMeshSceneNode *rightwing_node,
                   is::IMeshSceneNode *tail_node,
                   is::IMeshSceneNode *lefttail_node, is::IMeshSceneNode *righttail_node)
{
    ic::vector3df childRotation     = node          ->getRotation();
    ic::vector3df leftwingRotation  = leftwing_node ->getRotation();
    ic::vector3df rightwingRotation = rightwing_node->getRotation();
    ic::vector3df tailRotation      = tail_node     ->getRotation();
    ic::vector3df lefttailRotation  = lefttail_node ->getRotation();
    ic::vector3df righttailRotation = righttail_node->getRotation();

    if((m_stallSpeed < m_planeSpeed && m_stallSpeed * 1.1 > m_planeSpeed
            && (childRotation.X < -0.1 || childRotation.X > 0.1))
            || m_planeSpeedFloor > 1.1 * m_flatStallSpeed)
        m_isAlmostStalling = true;
    else
        m_isAlmostStalling = false;
    if((m_stallSpeed > m_planeSpeed
        && (childRotation.X < -0.1 || childRotation.X > 0.1))
        || m_flatStallSpeed >= m_planeSpeedFloor)
    {
        m_isStalling = true;
        m_planeAltitude -= m_stallStep;
    }
    else
        m_isStalling = false;

    //Increase or decrease the plane speed
    if(m_keyIsDown[KEY_UP] == true && !m_isStalling)
    {
        if(m_motorPower < m_maxMotorPower)
            m_motorPower += m_motorStep;
    }
    if(m_keyIsDown[KEY_DOWN] == true && !m_isStalling)
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
    if(m_keyIsDown[KEY_KEY_D] == true && !m_isStalling)
    {
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
    if(m_keyIsDown[KEY_KEY_Q] == true && !m_isStalling)
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

    if(m_planeSpeed < m_motorPower / 5.0)
        m_planeSpeed += 0.05/m_planeWeight * m_motorPower;
    else if(m_planeSpeed > m_motorPower / 5.0)
        m_planeSpeed -= 0.05/m_planeWeight * m_motorPower;
    else
        m_planeSpeed  = m_motorPower;

    if(childRotation.X < 0)
        m_planeSpeedSlope = (1 + childRotation.X / 90) * m_planeSpeed;
    else if(childRotation.X == 0)
        m_planeSpeedSlope = m_planeSpeed;
    else if(childRotation.X > 0)
        m_planeSpeedSlope = (1 + childRotation.X / 90) * m_planeSpeed;

    m_planeSpeedFloor = cos(childRotation.X * core::DEGTORAD) * m_planeSpeedSlope;
    if(!m_isStalling)
        m_planeAltitude  -= sin(childRotation.X * core::DEGTORAD) * m_planeSpeedSlope;

    m_rotationAltitude = childRotation.X;

    //Compute rotation
    float planeSpeedMByS = fromGameUnitToKt(m_planeSpeed) * 1.852 * 0.277777777778;
    if(planeSpeedMByS > 0)
        m_rotationAngle -= (tan(childRotation.Z * core::DEGTORAD) * m_g / planeSpeedMByS) * core::RADTODEG / 20; // for real values /80

    //Compute the stall speed
    m_loadFactor = (1/cos(-childRotation.Z * core::DEGTORAD));
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

void EventReceiver::changeCameraPose(is::ICameraSceneNode *cameraNode)
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

void EventReceiver::updateCompass(CGUICompass* compass)
{

    if(m_keyIsDown[KEY_KEY_D] == true)
    {
        compass->setCompassHeading(5.0);
        //compass->setCompassRelativePosition();
    }
    else if(m_keyIsDown[KEY_KEY_Q] == true)
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
            m_isBrakes = !m_isBrakes;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_K && !m_keyIsDown[KEY_KEY_K]) // Behind camera
        {
            m_keyIsDown[KEY_KEY_K] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_K)
        {
            m_keyIsDown[KEY_KEY_K] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_L && !m_keyIsDown[KEY_KEY_L]) // Front camera
        {
            m_keyIsDown[KEY_KEY_L] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_L)
        {
            m_keyIsDown[KEY_KEY_L] = false;
        }
        if(event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_M && !m_keyIsDown[KEY_KEY_M]) // Top camera
        {
            m_keyIsDown[KEY_KEY_M] = true;
        }
        if(!event.KeyInput.PressedDown && event.KeyInput.Key == KEY_KEY_M)
        {
            m_keyIsDown[KEY_KEY_M] = false;
        }
    }
    return false;
}
