#ifndef HUMANDRIVER_H
#define HUMANDRIVER_H

#include "Controller/Keyboard.h"
#include "Drivers/Driver.h"
#include "Entity/Car.h"
#include "Renderer/Renderer.h"

#include <SFML/Window/Keyboard.hpp>


class HumanDriver : public Driver {
   
    bool m_active;
    Car* m_car;
    Renderer* m_renderer;
    Keyboard* m_keyboard;

public:
    Keyboard::Key left;
    Keyboard::Key right;
    Keyboard::Key up;
    Keyboard::Key down;

public:
    HumanDriver(Car* car, bool active = true) : m_car(car), m_active(active),
        m_keyboard(nullptr)
    { 
        left = Keyboard::Left;
        right = Keyboard::Right;
        up = Keyboard::Up;
        down = Keyboard::Down;
    }

    int update();
    bool isActive() { return m_active; }
    void setActive(bool active) { m_active = active; }
    float getFitness() { return -1; } 
    void updateFitness() { }

    void setKeyController(Keyboard* keycontroller);

    void setKeyBinding();
    sf::Keyboard::Key getKeyBinding();

};

#endif