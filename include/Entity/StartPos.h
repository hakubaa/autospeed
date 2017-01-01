#ifndef STARTPOS_H
#define STARTPOS_H

#include "Entity/Types.h"
#include "Entity/Spec/StartPosSpec.h"
#include "Entity/Entity.h"
#include "deg2rad.h"

#include <Box2D/Box2D.h>


class StartPos : public Entity
{
    StartPosSpec m_spec;
    //b2World* m_world;
    //b2Body* m_body;

public:
    StartPos(StartPosSpec spec, b2World* world);
    ~StartPos();

    const b2Vec2& getPosition() const;
    //b2Body* getMainBody() const;
    EntType getType() const;
    const StartPosSpec& getSpec() const;

    float getAngle() const;

};

inline EntType StartPos::getType() const
{
    return m_spec.getType();
}

#endif