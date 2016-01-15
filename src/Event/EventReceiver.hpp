#pragma once

#ifndef EVENTRECEIVER
#define EVENTRECEIVER

#include "irrlicht.h"


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
    float getSpeed(){       return m_planeSpeedFloor;   }

    /* float getRotation: getter for the rotation value (plane go to the left or the right)
     * return:  rotationAngle: the rotation value
    */
    float getRotation(){    return m_rotationAngle;     }

    /* float getOnFloor: getter for the onFloor boolean value
     * return:  onFloor: the value define if the plane is on the floor
    */
    bool getOnFloor(){      return m_onFloor;           }

    /* float getInTakeOff: getter for the inTakeOff boolean value
     * return:  inTakeOff: the value define if the plane is taking off
    */
    bool getInTakeOff(){    return m_inTakeOff;         }

    /* float getInFlight: getter for the inFlight boolean value
     * return:  inFlight: the value define if the plane is flying
    */
    bool getInFlight(){     return m_inFlight;          }

    /* float getInLanding: getter for the getLanding boolean value
     * return:  inLanding: the value define if the plane is landing
    */
    bool getInLanding(){    return m_inLanding;         }

    /* float getIsStalling: getter for the isStalling boolean value
     * return:  isStalling: the value define if the plane is stalling
    */
    bool getIsStalling(){   return m_isStalling;        }

    /* void setPlaneWeight: function used to initialize the planeWeight
     * params:  const float planeWeight:      the plane weight
    */
    void setPlaneWeight(const float planeWeight){     m_planeWeight = planeWeight;    }

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
    void planeInTakeOff(irr::scene::ISceneNode *node);

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
    void planeInLanding(irr::scene::ISceneNode *node);

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

    //Init steps
    const float m_speedStep         = 0.005f;
    const float m_motorStep         = 0.01f;
    const float m_altitudeAngleStep = 0.1;
    const float m_rotationAngleStep = 0.1f;

    //Init plane constructor parameters
    const float m_voidPlaneWeightKg = 957.0f;     //Fuel included
    const float m_g = 9.81f;  //m.s-2

    const float m_wingLoading = 68.84f; //Charge alaire kg.m-2

    const float m_minPlaneSpeedKt  = 0.0f;    //Kt
    const float m_maxPlaneSpeedKt  = 158.0f;  //Kt
    const float m_flatStallSpeedKt = 44.0f;   //Kt

    //Init motor const
    const float m_minMotorPower = 0.0f;
    const float m_maxMotorPower = 16.0f;

    const float m_minPlaneSpeed   = fromKtToGameUnit(m_minPlaneSpeedKt);    //Irrlicht unit
    const float m_maxPlaneSpeed   = fromKtToGameUnit(m_maxPlaneSpeedKt);    //Irrlicht unit
    const float m_flatStallSpeed  = fromKtToGameUnit(m_flatStallSpeedKt);   //Irrlicht unit

    //Init plane limits values
    float m_loadFactor = 1.0f;    //No unit
    float m_stallSpeed = -100.0f; //Irrlicht unit

    //Moving plane values
    float m_planeWeight;
    float m_planeSpeed;
    float m_planeSpeedFloor;
    float m_planeSpeedSlope;
    float m_planeAltitude;
    float m_rotationAngle;

    float m_motorPower;

    const float m_weight = m_planeWeight * m_g;

    bool m_isBrakes;
    bool m_isStalling;
    bool m_isCrashed;

    bool m_onFloor;
    bool m_inTakeOff;
    bool m_inFlight;
    bool m_inLanding;
};

#endif
