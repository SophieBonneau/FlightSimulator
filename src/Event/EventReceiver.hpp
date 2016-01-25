#pragma once

#ifndef EVENTRECEIVER
#define EVENTRECEIVER

#include "irrlicht.h"
#include "../GUI/CGUICompass.hpp"
#include <iostream>
#include <vector>


class EventReceiver : public irr::IEventReceiver
{
public:
    /************************************************************************************/
    /******************************** Constructors **************************************/
    /************************************************************************************/
    EventReceiver();

    ~EventReceiver(){}

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* float getSpeed: getter for the speed value
     * return:  planeSpeed: the speed value
    */
    float getAltitude(){    return m_planeAltitude;     }

    /* float getAltitude: getter for the altitude value
     * return:  planeAltitude: the altitude value
    */
    float getFloorSpeed(){       return fromMStoGameUnit(m_planeFloorSpeed);   }

    float getAltitudeSpeed(){    return fromMStoGameUnit(m_planeAltitudeSpeed);   }

    float getSpeedKmH(){    return fromMSToKmH(m_planeFloorSpeed);      }

    float getAltitudeM(){   return fromGameUnitToM(m_planeAltitudeSpeed);    }

    /*float getAltitudeSpeed(){   if(!m_isStalling)
                                    return -fromGameUnitToKt(fromKtToKmH(fromKmToMS(sin(m_rotationAltitude * core::DEGTORAD) * m_planeSpeedX - cos(m_rotationAltitude * core::DEGTORAD) * m_planeSpeedY)));
                                return -1.0f;}*/

    float getSlopePercent() {   return -m_rotationAltitude / 90;    }

    float getFuelLiter() {   return m_fuelLiter / 152.0f * 100;    }

    /* float getRotation: getter for the rotation value (plane go to the left or the right)
     * return:  rotationAngle: the rotation value
    */
    float getRotation(){    return m_rotationAngle;     }

    /* bool getOnFloor: getter for the onFloor boolean value
     * return:  onFloor: the value define if the plane is on the floor
    */
    bool getOnFloor(){      return m_onFloor;           }

    /* bool getInTakeOff: getter for the inTakeOff boolean value
     * return:  inTakeOff: the value define if the plane is taking off
    */
    bool getInTakeOff(){    return m_inTakeOff;         }

    /* bool getInFlight: getter for the inFlight boolean value
     * return:  inFlight: the value define if the plane is flying
    */
    bool getInFlight(){     return m_inFlight;          }

    /* bool getInLanding: getter for the getLanding boolean value
     * return:  inLanding: the value define if the plane is landing
    */
    bool getInLanding(){    return m_inLanding;         }

    /* bool getIsAlmostStalling: getter for the isAlmostStalling boolean value
     * return:  isAlmostStalling: the value define if the plane is about to stall
    */
    bool getIsAlmostStalling(){   return m_isAlmostStalling;        }

    /* bool getIsStalling: getter for the isStalling boolean value
     * return:  isStalling: the value define if the plane is stalling
    */
    bool getIsStalling(){   return m_isStalling;        }

    /* bool getIsCrashed: getter for the isCrashed boolean value
     * return:  isCrashed: the value define if the plane has crashed
    */
    bool getIsCrashed(){   return m_isCrashed;        }



    /* void setPlaneWeight: function used to initialize the planeWeight
     * params:  const float planeWeight:      the plane weight
    */
    void setPlaneWeight(const float planeWeight){     m_planeWeight = planeWeight;    }

    void setIsLanding(const bool isLanding){   m_inLanding = isLanding;      }

    /* void setIsCrashed: function used to initialize the state of the boolean value isCrash
     * params:  const float isCrashed:      the plane crashed = true
    */
    void setIsCrashed(const float isCrashed){ m_isCrashed   = isCrashed;
                                              m_isStalling  = false;
                                              m_onFloor     = false;
                                              m_inTakeOff   = false;
                                              m_inLanding   = false;
                                              m_inFlight    = false;}



    /************************************************************************************/
    /******************************** Functions *****************************************/
    /************************************************************************************/
    /* float fromKtToGameUnit: convert from Kt unit to irrlicht unit (kt = 1.852 km/h)
     * params:  float valueToConvert:      the value in Kt unit
     * return:  float:  the value converted
    */
    float fromKtToGameUnit(float valueToConvert);

    /* float fromGameUnitToKt: convert from irrlicht unit to Kt unit (kt = 1.852 km/h)
     * params:  float valueToConvert:      the value in irrlicht unit
     * return:  float:  the value converted
    */
    float fromGameUnitToKt(float valueToConvert);

    float fromKtToKmH(float valueToConvert);
    float fromGameUnitToM(float valueToConvert);
    float fromKmToMS(float valueToConvert);
    float fromMSToKmH(float valueToConvert);
    float fromNToGameUnit(float valueToConvert);
    float fromMStoGameUnit(float valueToConvert);

    void computeTemperatureFromTheAltitude();
    void computeAtmosphericPressure();
    void computeAirDensity();
    void computeLiftForce(float rotAngle);
    void computeTractiveForce();
    void computeSumForce(float rotAngle);

    /* void planeOnFloor:  Calculate the position of the plane and change it direction during the "on floor" phase.
     *                      Do all the computation for the first phase of the take off
     * params:  is::ISceneNode *node:   Instance of the global plane node
     *                                  (permit only to change the plane direction)
    */
    void planeOnFloor(irr::scene::ISceneNode *node);

    /* void planeInTakeOff:  Calculate the position of the plane and change it direction during the critical pahse of the take off.
     *                       All changed datas between 0 and 15 meters
     * params:  is::ISceneNode *node:   Instance of the global plane node
     *                                  (permit only to change the plane direction)
    */
    void planeInTakeOff(irr::scene::ISceneNode *node, irr::scene::IMeshSceneNode *leftwing_node, irr::scene::IMeshSceneNode *rightwing_node, irr::scene::IMeshSceneNode *tail_node, irr::scene::IMeshSceneNode *lefttail_node, irr::scene::IMeshSceneNode *righttail_node);

    /* void planeInFlight:  Calculate the position of the plane and change it direction.
     *                  All changed data s will be called by the main when nedded
     * params:  is::ISceneNode *node:   Instance of the global plane node
     *                                  (permit only to change the plane direction)
    */
    void planeInFlight(irr::scene::ISceneNode *node,
                       irr::scene::IMeshSceneNode *leftwing_node, irr::scene::IMeshSceneNode *rightwing_node,
                       irr::scene::IMeshSceneNode *tail_node,
                       irr::scene::IMeshSceneNode *lefttail_node, irr::scene::IMeshSceneNode *righttail_node);


    /* void planeInLanding:  Calculate the position of the plane and change it direction during the critical pahse of the landing.
     *                       All changed datas between 0 and 15 meters
     * params:  is::ISceneNode *node:   Instance of the global plane node
     *                                  (permit only to change the plane direction)
    */
    void planeInLanding(irr::scene::ISceneNode *node, scene::IMeshSceneNode *lefttail_node, scene::IMeshSceneNode *righttail_node);

    /* void changeCameraPose:  Change the position of the camera
     * params:  is::ICameraSceneNode *cameraNode:   Instance of the camera node
    */
    void changeCameraPose(irr::scene::ICameraSceneNode *cameraNode);


   /************************************************************************************/
   /******************************** Events ********************************************/
   /************************************************************************************/
    /* bool OnEvent:  Once the event is caught, manage the thing to do. It permit to have multiple keys down at the same time.
     *                It also permit to quit the application with the ESCAPE key.
     * params:  const SEvent &event:    Reference to the event which had been previously caught
    */
    bool OnEvent(const irr::SEvent &event);

private:

    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/
    //Table to get the state of the keys
    bool m_keyIsDown[irr::KEY_KEY_CODES_COUNT];

    //Init air density (depend of the altitude)
    // Normalized atmosphere
    // Temperature
    const float m_tempAt0Y      = 15.0f;                  //°C
    const float m_tempAt3000Y   = -4.5f;                  //°C
    const float m_tempAt0YInK   = m_tempAt0Y + 273.15f;   //K
    const float m_tempAt3000YInK        = m_tempAt3000Y + 273.15f; //K
    float       m_currentTemperature    = m_tempAt0YInK;  //K

    // Pressure
    const float m_pressureAt0 = 10132.5f;   //P
    float       m_atmosphericPressure = m_pressureAt0;  //P

    //Air density
    const float m_reynoldsNumber = 8.31432f;        //J/molK
    const float m_airMolarMasse  = 28.965f * 0.01f; //kg/mol
    const float m_densityAt0     = 1.184f;           //kg/m3
    float       m_currentDensity = m_densityAt0;    //kg/m3

    //Parameters force
    const float m_sizeWings = 16.16f;   //m^2
    const float m_cx = 0.0075f; //No unit
    const float m_cz = 0.5f;    //No Unit
    const float m_dt = 0.1;     //s
    const float m_planeWeightKg = 953.0f;   //Kg
    const float m_g  = 9.81f;    //m.s-2
    const float m_frictionCoeff = 1.0f; //No Unit

    //Forces
    float m_liftForce       = 0.0f;   //N
    float m_weightForce     = 0.0f;   //N
    float m_ledForce        = 0.0f;   //N
    float m_tractiveForce   = 0.0f;   //N

    //Sum forces
    float m_sumForceX = 0.0f;   //N
    float m_sumForceY = 0.0f;   //N
    float m_sumForce  = 0.0f;   //N

    //Speed
    irr::core::vector3df m_planeSpeed = irr::core::vector3df(0.0f,0.0f, 0.0f);   //m/s

    float m_planeFloorSpeed = 0.0f;
    float m_planeAltitudeSpeed = 0.0f;

    //Init steps
    const float m_wingsRotationStep = 0.1f;
    const float m_speedStep         = 0.005f;
    const float m_motorStep         = 10.0f;
    const float m_altitudeAngleStep = 0.05f;
    const float m_rotationAngleStep = 0.1f;

    //Init plane constructor parameters
    const float m_minPlaneSpeedKt  = 0.0f;    //Kt
    const float m_maxPlaneSpeedKt  = 158.0f;  //Kt
    const float m_flatStallSpeedKt = 44.0f;   //Kt

    //Init motor const
    //const float m_speedMotorMax = 2700.0;  //tours/min
    //const float m_motorPowerMax = 180.0 * 735.398; //180ch in W at 2700tr/min
    //const float m_coupleMotorMax = m_motorPowerMax / m_speedMotorMax;   //N.m

    const float m_motorForceMin = 0.0f; //N
    const float m_motorForceMax = 600.0f;   //N

    const float m_minMotorPower = 0.0f;
    const float m_maxMotorPower = 2.0f;

    const float m_minPlaneSpeed   = fromKtToKmH(fromKmToMS(m_minPlaneSpeedKt));    //m/s
    const float m_maxPlaneSpeed   = fromKtToKmH(fromKmToMS(m_maxPlaneSpeedKt));    //m/s
    const float m_flatStallSpeed  = fromKtToKmH(fromKmToMS(m_flatStallSpeedKt));   //m/s

    //Init plane limits values
    float m_loadFactor = 1.0f;    //No unit
    float m_stallSpeed = -100.0f; //Irrlicht unit
    float m_stallStep = 0.1f;

    //Moving plane values
    float m_planeWeight;
    float m_planeSpeedX;
    float m_planeSpeedY;
    //float m_planeSpeed;
    float m_planeSpeedFloor;    //m/s
    float m_planeSpeedSlope;
    float m_planeAltitude;
    float m_rotationAngle;
    float m_rotationAltitude;

    float m_motorPower;
    float m_motorForce = 0.0f;
    float m_fuelLiter;

    const float m_weight = m_planeWeight * m_g;

    bool m_isBrakes;
    bool m_isAlmostStalling;
    bool m_isStalling;
    bool m_isCrashed;

    bool m_onFloor;
    bool m_inTakeOff;
    bool m_inFlight;
    bool m_inLanding;

    //Coordinates of the camera
    irr::core::vector3df m_cameraPose;
};

#endif
