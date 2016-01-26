#include "EventReceiver.hpp"

using namespace irr;
namespace ic = irr::core;
namespace is = irr::scene;

EventReceiver::EventReceiver()
{
    // Init keyboard states
    for(unsigned int i = 0; i<KEY_KEY_CODES_COUNT; ++i)
    {
        m_keyIsDown[i] = false;
    }

    //Init forces
    m_weightForce = m_planeWeightKg * m_g;

    //Init camera
    m_cameraPose = ic::vector3df(0.0,0.0,0.0);

    //Init plane state
    m_onFloor    = true;
    m_inTakeOff  = false;
    m_inFlight   = false;
    m_inLanding  = false;

    m_isBrakes   = true;
    m_isAlmostStalling = false;
    m_isStalling = false;
    m_isCrashed  = false;

    //Init moving plane values
    m_planeWeight     = m_planeWeightKg;
    m_planeSpeedFloor = 0.0f;
    m_planeSpeedSlope = 0.0f;
    m_planeAltitude   = 8.7f;
    m_rotationAngle   = 0.0f;
    m_rotationAltitude = 0.0f;

    m_motorPower = 0.0f;
    m_fuelLiter = 152.0f;
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

float EventReceiver::fromMSToKmH(float valueToConvert)
{
    return valueToConvert / 0.277778;
}

float EventReceiver::fromNToGameUnit(float valueToConvert)
{
    return valueToConvert / 3000.0f;
}

float EventReceiver::fromMStoGameUnit(float valueToConvert)
{
    return valueToConvert / 0.2777778 / 1000.0;
}

void EventReceiver::computeTemperatureFromTheAltitude()
{
    float currentAltitude = fromGameUnitToM(m_planeAltitude);
    m_currentTemperature = ((m_tempAt0YInK - m_tempAt3000YInK)/(0 - 3000)) * currentAltitude
            + ((0 * m_tempAt0YInK - 3000 * m_tempAt0YInK)/(0 - 3000));
}

void EventReceiver::computeAtmosphericPressure()
{
    computeTemperatureFromTheAltitude();
    m_atmosphericPressure = m_pressureAt0 * pow((1 - ((0.0065 * fromGameUnitToM(m_planeAltitude)) / m_currentTemperature)), 5.255);
}

void EventReceiver::computeAirDensity()
{
    computeAtmosphericPressure();
    m_currentDensity = (m_atmosphericPressure * m_airMolarMasse) / (m_reynoldsNumber * m_currentTemperature);
}

void EventReceiver::computeLiftForce(float rotAngle)
{
    computeAirDensity();
    //float cz = - 2 * M_PI * rotAngle;
    float speed = m_planeSpeed.getLength();
    m_liftForce = 0.5 * m_currentDensity * m_sizeWings * m_cz * speed * speed;
}

void EventReceiver::computeTractiveForce()
{
    computeAirDensity();
    float speed = m_planeSpeed.getLength();
    m_tractiveForce = 0.5 * m_currentDensity * m_sizeWings * m_cx * speed * speed;
}

void EventReceiver::computeSumForce(float rotAngle)
{
    computeLiftForce(rotAngle);
    computeTractiveForce();

    std::cout<<"Lift force : "<<m_liftForce<<std::endl;
    std::cout<<"Weight force : "<<m_weightForce<<std::endl;
    std::cout<<"Led force : "<<m_ledForce<<std::endl;
    std::cout<<"Tractive force : "<<m_tractiveForce<<std::endl;

    //Add force de frottement
    if(m_onFloor)
        m_tractiveForce = m_tractiveForce;

    m_sumForceX = m_ledForce - m_tractiveForce + sin(rotAngle * core::DEGTORAD) * m_weightForce;
    m_sumForceY = m_liftForce - cos(rotAngle * core::DEGTORAD) * m_weightForce;
}

void EventReceiver::planeOnFloor(is::ISceneNode *node)
{
    ic::vector3df childRotation = node->getRotation();

    if(m_keyIsDown[KEY_UP] == true)
    {
        if(m_ledForce < m_motorForceMax)
            m_ledForce += m_motorStep;
    }
    if(m_keyIsDown[KEY_DOWN] == true)
    {
        if(m_ledForce > m_motorForceMin)
            m_ledForce -= m_motorStep;
        else
            m_ledForce = m_motorForceMin;
    }

    // Get the plane up or down
    if(m_keyIsDown[KEY_KEY_Z] == true && !m_isBrakes)
    {
        if(m_sumForceY > 0)
        {
            m_onFloor   = false;
            m_inTakeOff = true;
        }
        childRotation.X -= 5 * m_altitudeAngleStep;
    }
    if(m_keyIsDown[KEY_KEY_S] == true && !m_isBrakes)
    {
        if(m_sumForceY < 0 && childRotation.X > 0)
        {
            m_onFloor   = false;
            m_isCrashed = true;
        }
        childRotation.X += 5 *m_altitudeAngleStep;
    }

    // Open the side panels of the plane to turn to the right or the left
    if(m_planeSpeedX != 0)
    {
        if(m_keyIsDown[KEY_KEY_D] == true && !m_isBrakes)
            m_rotationAngle += 2 * m_rotationAngleStep;
        if(m_keyIsDown[KEY_KEY_Q] == true && !m_isBrakes)
            m_rotationAngle -= 2 * m_rotationAngleStep;
    }

    node->setRotation(childRotation);

    if(!m_isBrakes)
    {
        computeSumForce(childRotation.X);

        m_planeSpeedX += m_sumForceX / m_planeWeight * m_dt;

        if(m_planeSpeedX < 0)
            m_planeSpeedX = 0;

        m_planeSpeed.X = m_planeSpeedX;
        m_planeFloorSpeed = m_planeSpeedX;

        if(m_sumForceY > 0 && childRotation.X > 0)
        {
            m_onFloor   = false;
            m_inTakeOff = true;
        }

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

    if(m_isStalling)
    {
        computeSumForce(childRotation.X);
        m_planeAltitudeSpeed = - 5 * m_sumForceY / m_planeWeight * m_dt;
    }
    else
    {
        if(m_keyIsDown[KEY_DOWN] == true)
        {
            if(m_sumForceY < 0)
                m_isStalling = true;
        }

        if(m_keyIsDown[KEY_KEY_Z] == true)
        {
            if(m_sumForceY > 0)
            {
                childRotation.X     -= m_altitudeAngleStep;
                lefttailRotation.X  -= m_wingsRotationStep;
                righttailRotation.X -= m_wingsRotationStep;
            }
            else
                m_isStalling = true;
        }
        if(m_keyIsDown[KEY_KEY_S] == true)
        {
            if(m_sumForceY > 0)
            {
                childRotation.X     += m_altitudeAngleStep;
                lefttailRotation.X  += m_wingsRotationStep;
                righttailRotation.X += m_wingsRotationStep;
            }
            else
                m_isStalling = true;
        }

        // Open the side panels of the plane to turn to the right or the left
        if(m_keyIsDown[KEY_KEY_D] == true)
        {
            if(childRotation.Z <= 0)
            {
                childRotation.Z     -= 40 * m_rotationAngleStep;
                leftwingRotation.X  -= m_wingsRotationStep;
                rightwingRotation.X += m_wingsRotationStep;
                tailRotation.Y      -= m_wingsRotationStep;
                tailRotation.Z      += m_wingsRotationStep / 2;
                m_isStalling         = true;
            }
        }
        if(m_keyIsDown[KEY_KEY_Q] == true)
        {
            if(childRotation.Z >= 0)
            {
                childRotation.Z     += 40 * m_rotationAngleStep;
                leftwingRotation.X  += m_wingsRotationStep;
                rightwingRotation.X -= m_wingsRotationStep;
                tailRotation.Y      += m_wingsRotationStep;
                tailRotation.Z      -= m_wingsRotationStep / 2;
                m_isStalling         = true;
            }
        }

        node->setRotation(childRotation);

        computeSumForce(childRotation.X);

        m_planeSpeedX += m_sumForceX / m_planeWeight * m_dt;
        m_planeSpeedY += 0.001 * m_sumForceY / m_planeWeight * m_dt;

        m_planeSpeed.X = m_planeSpeedX;
        m_planeSpeed.Y = m_planeSpeedY;

        m_planeFloorSpeed      = cos(childRotation.X * core::DEGTORAD) * m_planeSpeedX - sin(childRotation.X * core::DEGTORAD) * m_planeSpeedY;
        m_planeAltitudeSpeed   = cos(childRotation.X * core::DEGTORAD) * m_planeSpeedY - sin(childRotation.X * core::DEGTORAD) * m_planeSpeedX;

        m_rotationAltitude = childRotation.X;

        if(m_planeSpeed.getLength() < m_flatStallSpeed)
            m_isStalling = true;

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

    //If there is stall speed
    /*if((m_stallSpeed < m_planeSpeedX && m_stallSpeed * 1.1 > m_planeSpeedX)
            || (m_sumForceX > 0 && m_sumForceX < 100))
        m_isAlmostStalling = true;
    else
        m_isAlmostStalling = false;

    if(m_stallSpeed > m_planeSpeedX
        || m_sumForceX <= 0)
    {
        m_isStalling = true;
        m_planeAltitude += fromNToGameUnit(m_sumForceY) / m_planeWeight * m_dt;
    }
    else
        m_isStalling = false;
        */

    if((m_stallSpeed < m_planeSpeedX && m_stallSpeed * 1.1 > m_planeSpeedX)
            || (m_sumForceX > 0 && m_sumForceX < 100))
        m_isAlmostStalling = true;
    else
        m_isAlmostStalling = false;

    if(m_stallSpeed > m_planeSpeedX
        || m_sumForceX <= 0)
    {
        m_isStalling = true;
        m_planeAltitudeSpeed = -5 * m_sumForceY / m_planeWeight * m_dt;
    }
    else
        m_isStalling = false;

    //Increase or decrease the plane speed
    if(m_keyIsDown[KEY_UP] == true && !m_isStalling)
    {
        if(m_ledForce < m_motorForceMax)
            m_ledForce += m_motorStep;
    }
    if(m_keyIsDown[KEY_DOWN] == true && !m_isStalling)
    {
        if(m_ledForce > m_motorForceMin)
            m_ledForce -= m_motorStep;
        else
            m_ledForce = m_motorForceMin;
    }

    // Get the plane up or down
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

    // Open the side panels of the plane to turn to the right or the left
    if(m_keyIsDown[KEY_KEY_D] == true && !m_isStalling)
    {
        // If the plane is flat (not in the wrong inclinaison)
        if(childRotation.Z <= 0)
        {
            childRotation.Z     -= m_rotationAngleStep;
            leftwingRotation.X  -= m_wingsRotationStep;
            rightwingRotation.X += m_wingsRotationStep;
            tailRotation.Y      -= m_wingsRotationStep;
            tailRotation.Z      += m_wingsRotationStep / 2.0;
        }
        else
        {
            childRotation.Z     -= 2 * m_rotationAngleStep;
            leftwingRotation.X  -= 2 * m_wingsRotationStep;
            rightwingRotation.X += 2 * m_wingsRotationStep;
            tailRotation.Y      -= 2 * m_wingsRotationStep;
            tailRotation.Z      += m_wingsRotationStep;
        }
    }
    if(m_keyIsDown[KEY_KEY_Q] == true && !m_isStalling)
    {
        if(childRotation.Z >= 0)
        {
            childRotation.Z     += m_rotationAngleStep;
            leftwingRotation.X  += m_wingsRotationStep;
            rightwingRotation.X -= m_wingsRotationStep;
            tailRotation.Y      += m_wingsRotationStep;
            tailRotation.Z      -= m_wingsRotationStep / 2.0;
        }
        else
        {
            childRotation.Z     += 2 * m_rotationAngleStep;
            leftwingRotation.X  += 2 * m_wingsRotationStep;
            rightwingRotation.X -= 2 * m_wingsRotationStep;
            tailRotation.Y      += 2 * m_wingsRotationStep;
            tailRotation.Z      -= m_wingsRotationStep;
        }
    }

    node->setRotation(childRotation);

    computeSumForce(childRotation.X);

    m_planeSpeedX += m_sumForceX / m_planeWeightKg * m_dt;
    m_planeSpeedY += 0.001 * m_sumForceY / m_planeWeightKg * m_dt;

    m_planeSpeed = core::vector3df(m_planeSpeedX, m_planeSpeedY, 0.0f);

    m_planeFloorSpeed = cos(childRotation.X * core::DEGTORAD) * m_planeSpeedX - sin(childRotation.X * core::DEGTORAD) * m_planeSpeedY;
    if(!m_isStalling)
        m_planeAltitudeSpeed  = cos(childRotation.X * core::DEGTORAD) * m_planeSpeedY - sin(childRotation.X * core::DEGTORAD) * m_planeSpeedX;

    m_rotationAltitude = childRotation.X;

    // Compute rotation
    if(m_planeSpeedX > 0)
        m_rotationAngle -= (tan(childRotation.Z * core::DEGTORAD) * m_g / m_planeSpeedX) * core::RADTODEG / 20; // for real values /80

    // Compute the stall speed
    m_loadFactor = (1/cos(-childRotation.Z * core::DEGTORAD));
    m_stallSpeed = sqrt(m_loadFactor) * m_flatStallSpeed;

    node            ->setRotation(childRotation);
    leftwing_node   ->setRotation(leftwingRotation);
    rightwing_node  ->setRotation(rightwingRotation);
    tail_node       ->setRotation(tailRotation);
    lefttail_node   ->setRotation(lefttailRotation);
    righttail_node  ->setRotation(righttailRotation);
}

void EventReceiver::planeInLanding(is::ISceneNode *node, is::IMeshSceneNode *lefttail_node, is::IMeshSceneNode *righttail_node)
{
    ic::vector3df childRotation     = node          ->getRotation();
    ic::vector3df lefttailRotation  = lefttail_node ->getRotation();
    ic::vector3df righttailRotation = righttail_node->getRotation();

    // Increase or decrease the plane speed
    if(m_keyIsDown[KEY_UP] == true && !m_isStalling)
    {
        if(m_ledForce < m_motorForceMax)
            m_ledForce += m_motorStep;
    }
    if(m_keyIsDown[KEY_DOWN] == true && !m_isStalling)
    {
        if(m_ledForce > m_motorForceMin)
            m_ledForce -= m_motorStep;
        else
            m_ledForce = m_motorForceMin;
    }

    // Get the plane up or down
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

    // Open the side panels of the plane to turn to the right or the left
    if(m_keyIsDown[KEY_KEY_D] == true && !m_isStalling)
    {
        // If the plane is flat (not in the wrong inclinaison)
        if(childRotation.Z <= 0)
            childRotation.Z     -= m_rotationAngleStep;
        else
            childRotation.Z     -= 2 * m_rotationAngleStep;
    }
    if(m_keyIsDown[KEY_KEY_Q] == true && !m_isStalling)
    {
        if(childRotation.Z >= 0)
            childRotation.Z     += m_rotationAngleStep;
        else
            childRotation.Z     += 2 * m_rotationAngleStep;
    }

    node->setRotation(childRotation);

    computeSumForce(childRotation.X);

    m_planeSpeedX += fromNToGameUnit(m_sumForceX) / m_planeWeight * m_dt;
    m_planeSpeedY = fromNToGameUnit(m_sumForceY) / m_planeWeight * m_dt;

    m_planeSpeedFloor = cos(childRotation.X * core::DEGTORAD) * m_planeSpeedX - sin(childRotation.X * core::DEGTORAD) * m_planeSpeedY;
    m_planeAltitude  -= (sin(childRotation.X * core::DEGTORAD) * m_planeSpeedX - cos(childRotation.X * core::DEGTORAD) * m_planeSpeedY);

    m_rotationAltitude = childRotation.X;

    node            ->setRotation(childRotation);
    lefttail_node   ->setRotation(lefttailRotation);
    righttail_node  ->setRotation(righttailRotation);
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
