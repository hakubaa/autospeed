#ifndef LAZYMODE_H
#define LAZYMODE_H

#include "CarSim/EditorMode/BaseMode.h"
#include "CarSim/TrackEditor.h"

#include <SFML/Graphics.hpp>

class LazyMode : public BaseMode  {

    TrackEditor* m_editor;

public:
    LazyMode(TrackEditor* editor);

    void handleEvent(const sf::Event& event);
    std::string getInfo() const;
    std::string getStatus() const;
    void update(sf::Time timeStep);
};

#endif