#include "SimMode/RaceMode.h"

RaceMode::RaceMode(b2World* world, Renderer* renderer) :
    SimMode(renderer),
    m_world(world)
{
}

RaceMode::~RaceMode()
{
}

void RaceMode::addDriver(Driver* driver) {
    m_drivers.push_back(driver);
}

void RaceMode::update(const sf::Time& timeStep) 
{
    // Evaluate all drivers
    for(std::vector<Driver*>::iterator driver = m_drivers.begin(); driver != m_drivers.end(); ++driver) 
        if ((*driver)->isActive()) 
            (*driver)->update();

    // Update world simulation
    m_world->Step(timeStep.asSeconds(), velocityIterations, positionIterations);
}

void RaceMode::initSim()
{
}