#ifndef RACEMODE_H
#define RACEMODE_H

#include "SimMode/SimMode.h"
#include "Renderer/Renderer.h"
#include "Drivers/Driver.h"

#include <Box2D/Box2D.h>

class RaceMode : public SimMode {

protected:
    void update(const sf::Time& timeStep);
    void initSim();

private:
        // parameters for updating world - they would not be changed
    constexpr static const int velocityIterations = 6;   
    constexpr static const int positionIterations = 2;

    b2World* m_world;
    std::vector<Driver*> m_drivers;

public:
    RaceMode(b2World* world, Renderer* renderer);
    ~RaceMode();

    void addDriver(Driver* driver);
};

#endif