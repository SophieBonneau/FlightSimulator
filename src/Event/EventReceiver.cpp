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
