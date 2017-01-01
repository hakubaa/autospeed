#include "SimMode/SimMode.h"

// parameters for updating world - they would not be changed
constexpr int velocityIterations = 6;   
constexpr int positionIterations = 2;


SimMode::SimMode()
    : m_world(b2Vec2(0.0f, 0.0f))
{
    std::cout << "SimMode::SimMode()" << std::endl;
    // set collision listener for physics engine
    m_world.SetContactListener(&m_entsListener);    
}

void SimMode::update(const sf::Time& timeStep)
{
    m_world.Step(timeStep.asSeconds(), velocityIterations, 
        positionIterations);
}

/*-------------------------------------------------------
    Observer pattern.
---------------------------------------------------------*/

void SimMode::notify(event_t et)
{
    for(auto it = m_observers.begin(); it != m_observers.end(); it++)
        (*it)->update(et);
}

void SimMode::addObserver(SimMode::Observer* observer)
{
    m_observers.push_back(observer);
}