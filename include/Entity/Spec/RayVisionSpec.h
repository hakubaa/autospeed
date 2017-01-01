#ifndef RAYVISIONSPEC_H
#define RAYVISIONSPEC_H

#include "Entity/Types.h"
#include "Entity/Spec/EntitySpec.h"
#include "tinyxml2.h"

#include <Box2D/Box2D.h>

class RayVisionSpec : public EntitySpec {
public:

    int n;
    float length;
    bool showRays;
    bool dynamicRays;
    std::uint16_t filter;
    float maxRayAngle;

    RayVisionSpec() : n(0), length(0), showRays(false), dynamicRays(false), filter(0x0000),
        maxRayAngle(90) { }

    EntType getType() const;
};

inline EntType RayVisionSpec::getType() const
{
    return EntType::ENT_RAYVISION;
}


#endif