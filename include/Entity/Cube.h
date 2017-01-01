#ifndef CUBE_H
#define CUBE_H

#include "Entity/Types.h"
#include "Entity/Entity.h"
#include "Entity/Spec/CubeSpec.h"

#include <Box2D/Box2D.h>


class Cube : public Entity {

    CubeSpec m_spec;
    //b2World* m_world;

public:
    //b2Body* m_body;

public:
    Cube(CubeSpec spec, b2World* world);
    ~Cube();

    const b2Vec2& getPosition() const;
    //b2Body* getMainBody() const;
    EntType getType() const;
    const CubeSpec& getSpec() const;
};

inline EntType Cube::getType() const
{
    return m_spec.getType();
}

#endif