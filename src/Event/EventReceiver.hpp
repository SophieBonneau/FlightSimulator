#pragma once

#ifndef EVENTRECEIVER
#define EVENTRECEIVER

#include "irrlicht.h"

using namespace irr;

class EventReceiver : public IEventReceiver
{
public:
    // Constructor
    EventReceiver();
    // Destructor
    ~EventReceiver(){}

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* float getSpeed: getter for the speed value
     * return:  planeSpeed: the speed value
    */
    float getAltitude(){    return planeAltitude;  }

    /* float getAltitude: getter for the altitude value
     * return:  planeAltitude: the altitude value
    */
    float getSpeed(){    return planeSpeedFloor;  }

    /* float getRotation: getter for the rotation value (plane go to the left or the right)
     * return:  rotationAngle: the rotation value
    */
    float getRotation(){    return rotationAngle;  }

    /* float getOnFloor: getter for the onFloor boolean value
     * return:  onFloor: the value definig if the plane is on the floor
    */
    float getOnFloor(){    return onFloor;  }

    /* float getInTakeOff: getter for the inTakeOff boolean value
     * return:  inTakeOff: the value definig if the plane is taking off
    */
    float getInTakeOff(){    return inTakeOff;  }

    /* float getInFlight: getter for the inFlight boolean value
     * return:  inFlight: the value definig if the plane is flying
    */
    float getInFlight(){    return inFlight;  }

    /* float getInLanding: getter for the getLanding boolean value
     * return:  inLanding: the value definig if the plane is landing
    */
    float getInLanding(){    return inLanding;  }

    /* float getIsStalling: getter for the isStalling boolean value
     * return:  isStalling: the value definig if the plane is stalling
    */
    float getIsStalling(){    return isStalling;  }

    /* void setPlaneWeight: function used to initialize the planeWeight
     * params:  const float planeWeight:      the plane weight
    */
    void setPlaneWeight(const float planeWeight){     this->planeWeight = planeWeight;    }




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
   bool OnEvent(const SEvent &event);

private:

    bool keyIsDown[KEY_KEY_CODES_COUNT];

    //Init steps
    const float speedStep         = 0.005f;
    const float motorStep         = 0.01f;
    const float altitudeAngleStep = 0.1;
    const float rotationAngleStep = 0.1f;

    //Init plane constructor parameters
    const float voidPlaneWeightKg = 957.0f;     //Fuel included
    const float g = 9.81f;  //m.s-2

    const float wingLoading = 68.84f; //Charge alaire kg.m-2

    const float minPlaneSpeedKt  = 0.0f;    //Kt
    const float maxPlaneSpeedKt  = 158.0f;  //Kt
    const float flatStallSpeedKt = 44.0f;   //Kt

    //Init motor const
    const float minMotorPower = 0.0f;
    const float maxMotorPower = 16.0f;

    const float minPlaneSpeed   = fromKtToGameUnit(minPlaneSpeedKt);    //Irrlicht unit
    const float maxPlaneSpeed   = fromKtToGameUnit(maxPlaneSpeedKt);    //Irrlicht unit
    const float flatStallSpeed  = fromKtToGameUnit(flatStallSpeedKt);   //Irrlicht unit

    //Init plane limits values
    float loadFactor = 1.0f;    //No unit
    float stallSpeed = -100.0f; //Irrlicht unit

    //Moving plane values
    float planeWeight;
    float planeSpeed;
    float planeSpeedFloor;
    float planeAltitude;
    float rotationAngle;

    float motorPower;

    const float weight = planeWeight * g;

    float isBrakes;
    float isStalling;
    float isCrashed;

    bool onFloor;
    bool inTakeOff;
    bool inFlight;
    bool inLanding;

};

#endif
