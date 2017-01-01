#include "Entity/StartPos.h"


StartPos::StartPos(StartPosSpec spec, b2World* world) :
    Entity(world),
    // m_world(world),
    m_spec(spec)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = m_spec.pos;
    bodyDef.angle = m_spec.angle;
    m_body = world->CreateBody(&bodyDef);

    b2Vec2 vertices[5];
    vertices[0].Set(0, m_spec.height/2);
    vertices[1].Set(0.75*m_spec.width, m_spec.height/2);
    vertices[2].Set(m_spec.width, 0);
    vertices[3].Set(0.75*m_spec.width, -m_spec.height/2);
    vertices[4].Set(0, -m_spec.height/2);

    b2PolygonShape bodyDefShape;
    bodyDefShape.Set( vertices, 5 );

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.filter.groupIndex = -1;
    fixtureDef.shape = &bodyDefShape;

    m_body->CreateFixture(&fixtureDef);
    m_body->SetUserData(this);
}


StartPos::~StartPos()
{
//    m_world->DestroyBody(m_body);
}

const b2Vec2& StartPos::getPosition() const
{
    return m_body->GetPosition();
}

float StartPos::getAngle() const 
{
    return m_body->GetAngle() - 90 * DEGTORAD; // due to rotation in track editor
}

// b2Body* StartPos::getMainBody() const
// {
//     return m_body;
// }

// Entity::Type StartPos::getType() const
// {
//     return Entity::Type::ENT_STARTPOS;
// }

const StartPosSpec& StartPos::getSpec() const
{
    return m_spec;
}