#ifndef DRIVERFACTORY_H
#define DRIVERFACTORY_H

#include "Drivers/Driver.h"
#include "NEAT/organism.h"
#include "NEAT/genome.h"

#include <Box2D/Box2D.h>

class DriverFactory {
    
public:
    virtual Driver* create(NEAT::Organism*, b2World* world) = 0;
};

#endif