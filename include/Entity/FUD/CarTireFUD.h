#ifndef CARTIREFUD_H
#define CARTIREFUD_H

#include "Entity/FUD/FixtureUserData.h"

//class to allow marking a fixture as a car tire
class CarTireFUD : public FixtureUserData {
public:
    CarTireFUD() : FixtureUserData(FUD_CAR_TIRE) {}
};


#endif