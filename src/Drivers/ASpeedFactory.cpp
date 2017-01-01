#include "Drivers/ASpeedFactory.h"

Driver* ASpeedFactory::create(NEAT::Organism* org, b2World* world) {
    Car* car = new Car(m_spec, world);
    car->setTransform(m_pos, m_angle);
    AutoDriver* driver = new AutoDriver(org, car);
    return driver;  
}

void ASpeedFactory::setStartPos(b2Vec2 pos, float angle)
{
    m_pos = pos;
    m_angle = angle;
}