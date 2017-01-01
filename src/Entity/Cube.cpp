#include "Entity/Cube.h"

Cube::Cube(CubeSpec spec, b2World* world) : 
    Entity(world),
    // m_world(world), 
    m_spec(spec)
{
    b2BodyDef kwadrat;
    kwadrat.type = b2_staticBody;
    kwadrat.position = m_spec.pos;
    kwadrat.angle = m_spec.angle;
    kwadrat.linearDamping = 1.0f;
    m_body = m_world->CreateBody(&kwadrat);

    b2PolygonShape kwadratShape;
    kwadratShape.SetAsBox(m_spec.width, m_spec.height);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.shape = &kwadratShape;

    m_body->CreateFixture(&fixtureDef);

    m_body->SetUserData(this);
}

Cube::~Cube() {
//    m_world->DestroyBody(m_body);
}

const b2Vec2& Cube::getPosition() const {
    return m_body->GetPosition();
}

// b2Body* Cube::getMainBody() const {
//     return m_body;
// }

// Entity::Type Cube::getType() const {
//     return Entity::Type::ENT_CUBE;
// }

const CubeSpec& Cube::getSpec() const {
    return m_spec;
}