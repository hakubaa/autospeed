#ifndef TDCARDEF_H
#define TDCARDEF_H

#include "Entity/Types.h"
#include "Entity/Spec/EntitySpec.h"
#include "Entity/Spec/CarTireSpec.h"
#include "Entity/Spec/RayVisionSpec.h"

#include "tinyxml2.h"
#include <Box2D/Box2D.h>


class CarSpec : public EntitySpec {
public:

    int groupIndex;
    RayVisionSpec rayVision;
    CarTireSpec frontLeftTire;
    CarTireSpec frontRightTire;
    CarTireSpec backLeftTire;
    CarTireSpec backRightTire;
    // b2Vec2 pos;
    // float angle;

    CarSpec() :  groupIndex(-1)
        // , pos(0.0f, 0.0f), angle(0.0f) 
    { }

    EntType getType() const;

};

inline EntType CarSpec::getType() const
{
    return EntType::ENT_CAR;
}

#endif