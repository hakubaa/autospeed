#ifndef CUBESPEC_H
#define CUBESPEC_H

#include "Entity/Types.h"
#include "Entity/Spec/EntitySpec.h"

class CubeSpec : public EntitySpec {

public:

    float width;
    float height;
    b2Vec2 pos;
    float angle;

    CubeSpec() : pos(0.0f, 0.0f), width(0.0f), height(0.0f), angle(0.0f) { }

    EntType getType() const;
};

inline EntType CubeSpec::getType() const
{
    return EntType::ENT_CUBE;
}

#endif