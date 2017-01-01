#include "Entity/Node.h"

Node::Node(NodeSpec spec, b2World* world) : 
    Entity(world),
    // m_world(world), 
    m_spec(spec)
{ 
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = m_spec.pos;
    bodyDef.linearDamping = 1.0f;
    m_body = world->CreateBody(&bodyDef);

    b2CircleShape bodyShape;
    bodyShape.m_p.Set(0.0f, 0.0f);
    bodyShape.m_radius = m_spec.radius;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.shape = &bodyShape;

    m_body->CreateFixture(&fixtureDef);

    m_body->SetUserData(this);
}

Node::~Node() {
//    m_world->DestroyBody(m_body);
}

const b2Vec2& Node::getPosition() const {
    return m_body->GetPosition();
}

// b2Body* Node::getMainBody() const {
//     return m_body;
// }

// EntType Node::getType() const {
//     return m_spec.getType();
// }

const NodeSpec& Node::getSpec() const {
    return m_spec;
}