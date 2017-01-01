#ifndef AUTODRIVER_H
#define AUTODRIVER_H

#include "Drivers/Driver.h"
#include "NEAT/organism.h"
#include "NEAT/genome.h"
#include "Entity/Car.h"
#include "Entity/CarTire.h"

#include <cassert>
#include <iostream>

class AutoDriver : public Driver {

    bool active_;
    bool organismOwner_;
    double actThreshold_;
        
    // int steps_;
    // int* stateCounter_;
    // State lastState_;

    NEAT::Organism* organism_;
    Car* car_;

    void initialize();
public:

    AutoDriver(std::ifstream& genomFile, Car* car, bool randomize = false);
    AutoDriver(NEAT::Genome* genome, Car* car, int newId = -1);
    AutoDriver(NEAT::Organism* org, Car* car);
    ~AutoDriver();

    // return combination of: TDC_LEFT, TDC_RIGHT, TDC_UP, TDC_DOWN
    int update();
    void setActive(bool active) { car_->setActive(active); }
    bool isActive() { return car_->isActive(); }

    float getFitness() {
        return car_->getDrivenCheckpointsCount();
    }

    void updateFitness() {
        organism_->fitness = getFitness();
    }

    void setActThreshold(double threshold) {
        actThreshold_ = threshold;
    }
    
    // int getStepsNo() { return steps_; }
    // int getStateFreq(int index) { return stateCounter_[index]; }

    Car* getCar() {
        return car_;
    }

    NEAT::Organism* getOrganism() {
        return organism_;
    }

    void setOrganism(NEAT::Organism* organism) {
        organism_ = organism;
    }
};

#endif