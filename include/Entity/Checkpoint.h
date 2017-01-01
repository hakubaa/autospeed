#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "Entity/Types.h"
#include "Entity/Spec/CheckpointSpec.h"
#include "Entity/Entity.h"

#include <Box2D/Box2D.h>


class Checkpoint : public Entity {

public:
    //b2Body* m_body;

private:
    CheckpointSpec m_spec;
    //b2World* m_world;
    b2Fixture* m_tlFixture;

public:
    Checkpoint(CheckpointSpec spec, b2World* world);
    ~Checkpoint();

    const b2Vec2& getPosition() const;
    //b2Body* getMainBody() const;
    EntType getType() const;
    const CheckpointSpec& getSpec() const;
    
    int getOrderNo() const;
    int getChpointType() const;
};

inline EntType Checkpoint::getType() const
{
    return m_spec.getType();
}

#endif