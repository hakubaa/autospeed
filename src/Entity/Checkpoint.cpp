#include "Entity/Checkpoint.h"


Checkpoint::Checkpoint(CheckpointSpec spec, b2World* world) :
    Entity(world),
    m_spec(spec)
    // m_world(world)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    m_body = m_world->CreateBody(&bodyDef);

    b2EdgeShape tlShape;
    tlShape.Set(m_spec.sNode, m_spec.eNode);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.shape = &tlShape;
    fixtureDef.isSensor = true;
    
    m_tlFixture = m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}

Checkpoint::~Checkpoint() {
//    m_world->DestroyBody(m_body);
}

int Checkpoint::getOrderNo() const {
    return m_spec.orderNo;
}

int Checkpoint::getChpointType() const {
    return m_spec.type;
}

const b2Vec2& Checkpoint::getPosition() const {
    return m_body->GetPosition();
}

// b2Body* Checkpoint::getMainBody() const {
//     return m_body;
// }

// Entity::Type Checkpoint::getType() const {
//     return Entity::Type::ENT_CHECKPOINT;
// }

const CheckpointSpec& Checkpoint::getSpec() const {
    return m_spec;
}
