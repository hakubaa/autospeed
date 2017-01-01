#ifndef TDCAR_H
#define TDCAR_H

#include "Entity/Types.h"
#include "Entity/Spec/CarSpec.h"
#include "Entity/CarTire.h"
#include "Entity/RayVision.h"
#include "Entity/Entity.h"
#include "Entity/Checkpoint.h"

#include <Box2D/Box2D.h>

#include <vector>


class Car : public Entity 
{
    CarSpec m_spec;
    //b2World* m_world;

    std::vector<CarTire*> m_tires;
    b2RevoluteJoint *blJoint, *brJoint;
    b2RevoluteJoint *flJoint, *frJoint;
    b2WeldJoint* rvJoint;
    bool m_active;
    bool m_rvActive;
    Checkpoint* m_lastCheckpoint;
    int m_checkpointsNo;

public:
    //b2Body* m_body;
    RayVision* rayVision;

public:
    Car(CarSpec spec, b2World* world);
    ~Car();

    void update(int controlState);

    // Checkpoint should be traversed in ascending order
    void updateCheckpoint(Checkpoint *chpoint);
    Checkpoint* getLastCheckpoint() const;
    int getDrivenCheckpointsCount() const;

    bool isActive() const;
    bool setActive(bool active);

    void setTransform(const b2Vec2& position, float angle);

    const b2Vec2& getPosition() const;
    EntType getType() const;
    //b2Body* getMainBody() const;
    const CarSpec& getSpec() const;
    void handleCollision(Entity* ent);

    b2Vec2 getLinearVelocity() const;
};

inline Checkpoint* Car::getLastCheckpoint() const 
{ 
    return m_lastCheckpoint; 
}

inline int Car::getDrivenCheckpointsCount() const 
{ 
    return m_checkpointsNo; 
}

inline bool Car::isActive() const 
{ 
    return m_active; 
}

inline const b2Vec2& Car::getPosition() const {
    return m_body->GetPosition();
}

inline EntType Car::getType() const {
    return m_spec.getType();
}

// inline b2Body* Car::getMainBody() const {
//     return m_body;
// }

inline const CarSpec& Car::getSpec() const {
    return m_spec;
}

inline b2Vec2 Car::getLinearVelocity() const
{
    return m_body->GetLinearVelocity();
}

#endif