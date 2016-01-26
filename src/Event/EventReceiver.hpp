#pragma once

#ifndef EVENTRECEIVER
#define EVENTRECEIVER

#include "irrlicht.h"
#include "../GUI/CGUICompass.hpp"
#include <iostream>
#include <vector>

/* Class EventReceiver: inherits from the irr::IEventReceiver class. Manage the keyboard events
*/
class EventReceiver : public irr::IEventReceiver
{
public:
    /************************************************************************************/
    /******************************** Constructor **************************************/
    /************************************************************************************/
    /* Constructor EventReceiver: Initialize the global attributes of the class
    */
    EventReceiver();

    ~EventReceiver(){}

    /************************************************************************************/
    /******************************** Getters & setters *********************************/
    /************************************************************************************/
    /* irr::scene::IMeshSceneNode* getNode: get the specified object node for irrlicht purpose
     * return:  const irr::scene::IMeshSceneNode*: the current element node
    */
    bool* getKeyIsDown()     {   return m_keyIsDown;      }

   /************************************************************************************/
   /******************************** Events ********************************************/
   /************************************************************************************/
    /* bool OnEvent:  Once the event is caught, manage the actions to trigger. It can manage multiple keys down at the same time.
     *                We can quit the application with the ESCAPE key.
     * params:  const SEvent &event:    Reference to the event which had been previously caught
    */
    bool OnEvent(const irr::SEvent &event);

private:
    /************************************************************************************/
    /******************************** Attributes ****************************************/
    /************************************************************************************/
    //Table to get the state of the keys
    bool m_keyIsDown[irr::KEY_KEY_CODES_COUNT];

};

#endif
