#ifndef GROUNDAREAFUD_H
#define GROUNDAREAFUD_H

#include "Entity/FUD/FixtureUserData.h"


//class to allow marking a fixture as a ground area
class GroundAreaFUD : public FixtureUserData {
public:
    float frictionModifier;
    bool outOfCourse;
    
    GroundAreaFUD(float fm, bool ooc) : FixtureUserData(FUD_GROUND_AREA) {
        frictionModifier = fm;
        outOfCourse = ooc;
    }
};

#endif