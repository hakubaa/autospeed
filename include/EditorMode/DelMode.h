#ifndef DELMODE_H
#define DELMODE_H

#include "CarSim/Box2DQueryCallback.h"
#include "CarSim/EditorMode/BaseMode.h"
#include "CarSim/TrackEditor.h"
#include "CarSim/Entity/Node.h"
#include "CarSim/Entity/TrackLink.h"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <iostream>
#include <algorithm>

class DelMode : public BaseMode  {

    TrackEditor* m_editor;

public:
    DelMode(TrackEditor* editor);

    void handleEvent(const sf::Event& event);
    std::string getInfo() const;
    std::string getStatus() const;
    void update(sf::Time timeStep);
};

#endif