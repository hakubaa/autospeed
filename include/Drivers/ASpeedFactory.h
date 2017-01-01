#ifndef ASPEEDFACTORY_H
#define ASPEEDFACTORY_H

#include "Drivers/DriverFactory.h"
#include "Drivers/AutoDriver.h"
#include "Entity/Spec/CarSpec.h"
#include "Entity/Car.h"

#include <Box2D/Box2D.h>

class ASpeedFactory : public DriverFactory {
    
    CarSpec m_spec;
    b2Vec2 m_pos;
    float m_angle;

public:
    ASpeedFactory(const CarSpec& spec, b2Vec2 pos, float angle) : m_spec(spec),
         m_pos(pos), m_angle(angle) { }

    Driver* create(NEAT::Organism*, b2World* world);
    void setStartPos(b2Vec2 pos, float angle);
};

#endif