#include "CarSim/EditorMode/LazyMode.h"

LazyMode::LazyMode(TrackEditor* editor) : m_editor(editor) { }

void LazyMode::handleEvent(const sf::Event& event) {


}

void LazyMode::update(sf::Time timeStep)
{ 
}

std::string LazyMode::getStatus() const {
    std::stringstream s;

    return s.str();
}

std::string LazyMode::getInfo() const {
    std::stringstream s;

    return s.str();
}