#include "Drivers/HumanDriver.h"

int HumanDriver::update() 
{            
    m_car->rayVision->update();

    int controlState = 0;
    if (m_keyboard != nullptr)
    {
        if (m_keyboard->isKeyPressed(left))
            controlState |= CarTire::TDC_RIGHT;
        if (m_keyboard->isKeyPressed(right))
            controlState |= CarTire::TDC_LEFT;
        if (m_keyboard->isKeyPressed(up))
            controlState |= CarTire::TDC_UP;
        if (m_keyboard->isKeyPressed(down))
            controlState |= CarTire::TDC_DOWN;        

        m_car->update(controlState);   
    }

    return controlState;
}


void HumanDriver::setKeyController(Keyboard* keycontroller)
{
    m_keyboard = keycontroller;
}