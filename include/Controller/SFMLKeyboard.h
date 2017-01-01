#ifndef SFMLKEYBOARD_H
#define SFMLKEYBOARD_H

#include "Controller/Keyboard.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

class SFMLKeyboard : public Keyboard
{
public:
    void setKeyState(sf::Event::KeyEvent kevent, bool state);
};


#endif