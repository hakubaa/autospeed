#ifndef TDTIREDEF_H
#define TDTIREDEF_H

#include "Entity/Types.h"
#include "Entity/Spec/EntitySpec.h"

class CarTireSpec : public EntitySpec {

public:

    int groupIndex;
    float maxForwardSpeed;  
    float maxBackwardSpeed; ;
    float maxDriveForce;    
    float maxLateralImpulse;

    CarTireSpec() :  groupIndex(-1), maxForwardSpeed(0.0f), maxBackwardSpeed(0.0f), 
        maxDriveForce(0.0f), maxLateralImpulse(0.0f) { }

    EntType getType() const;
};

inline EntType CarTireSpec::getType() const
{
    return EntType::ENT_CARTIRE;
}

#endif