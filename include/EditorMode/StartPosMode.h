#ifndef STARTPOSMODE_H
#define STARTPOSMODE_H

#include "CarSim/EditorMode/BaseMode.h"
#include "CarSim/TrackEditor.h"
#include "CarSim/Entity/StartPos.h"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <string>


class StartPosMode : public BaseMode {

    TrackEditor* m_editor;
    StartPos* m_activeEnt;
    int m_entsCount;

public:
    StartPosMode(TrackEditor* editor);

    void handleEvent(const sf::Event& event);
    std::string getInfo() const;
    std::string getStatus() const;
    void update(sf::Time timeStep);
};

#endif