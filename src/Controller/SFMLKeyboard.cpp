#include "Controller/SFMLKeyboard.h"

void SFMLKeyboard::setKeyState(sf::Event::KeyEvent kevent, bool state)
{
    switch(kevent.code)
    {
        case sf::Keyboard::A:
            m_keystate[Keyboard::A] = state;
            break;

        case sf::Keyboard::W:
            m_keystate[Keyboard::W] = state;
            break;

        case sf::Keyboard::S:
            m_keystate[Keyboard::S] = state;
            break;

        case sf::Keyboard::D:
            m_keystate[Keyboard::D] = state;
            break;

        case sf::Keyboard::Left:
            m_keystate[Keyboard::Left] = state;
            break;

        case sf::Keyboard::Right:
            m_keystate[Keyboard::Right] = state;
            break;

        case sf::Keyboard::Up:
            m_keystate[Keyboard::Up] = state;
            break;

        case sf::Keyboard::Down:
            m_keystate[Keyboard::Down] = state;
            break;

        default:
            break;
    }
}