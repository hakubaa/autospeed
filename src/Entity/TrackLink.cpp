#include "Entity/TrackLink.h"

TrackLink::TrackLink(TrackLinkSpec spec, b2World* world) :
    Entity(world),
    m_spec(spec),
    // m_world(world),
    m_isSensor(spec.isSensor)
{

    b2BodyDef bodySpec;
    bodySpec.type = b2_staticBody;
    m_body = m_world->CreateBody(&bodySpec);

    b2EdgeShape tlShape;
    tlShape.Set(m_spec.sNode, m_spec.eNode);

    b2FixtureDef fixtureSpec;
    fixtureSpec.density = 1.0f;
    fixtureSpec.shape = &tlShape;
    fixtureSpec.isSensor = m_spec.isSensor;
    
    m_tlFixture = m_body->CreateFixture(&fixtureSpec);
    m_body->SetUserData(this);

}

TrackLink::~TrackLink() 
{
//    m_world->DestroyBody(m_body);
}

void TrackLink::setSensor(bool isSensor) 
{
    if (m_isSensor != isSensor) 
    {
        m_isSensor = isSensor;
        m_tlFixture->SetSensor(m_isSensor);
    }
}

const b2Vec2& TrackLink::getPosition() const 
{
    return m_body->GetPosition();
}

// b2Body* TrackLink::getMainBody() const 
// {
//     return m_body;
// }

// Entity::Type TrackLink::getType() const 
// {
//     return Entity::Type::ENT_TRACKLINK;
// }

const TrackLinkSpec& TrackLink::getSpec() const {
    return m_spec;
}