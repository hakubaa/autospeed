#ifndef BASEMODE_H
#define BASEMODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include <string>
#include <sstream>

// #include <iostream>

class TrackEditor;

class BaseMode  {

public:
    virtual ~BaseMode() {}
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual std::string getInfo() const = 0;
    virtual std::string getStatus() const = 0;
    virtual void update(sf::Time timeStep) = 0;
};

#endif