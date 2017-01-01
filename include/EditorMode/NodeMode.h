#ifndef NODEMODE_H
#define NODEMODE_H

#include "CarSim/EditorMode/BaseMode.h"
#include "CarSim/TrackEditor.h"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <iostream>

class NodeMode : public BaseMode  {

    TrackEditor* m_editor;

public:
    NodeMode(TrackEditor* editor);

    void handleEvent(const sf::Event& event);
    std::string getInfo() const;
    std::string getStatus() const;
    void update(sf::Time timeStep);
};

#endif