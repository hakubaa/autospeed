#include "Entity/Car.h"


Car::Car(CarSpec spec, b2World* world) : 
    Entity(world),
    m_spec(spec), 
    // m_world(world),
    m_active(true), 
    m_rvActive(true),
    m_lastCheckpoint(0), 
    m_checkpointsNo(0) 
{
    //create car body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    m_body = m_world->CreateBody(&bodyDef);
    m_body->SetAngularDamping(3);
    m_body->SetActive(m_active);

    b2Vec2 vertices[8];
    vertices[0].Set( 1.5,   0);
    vertices[1].Set(   3, 2.5);
    vertices[2].Set( 2.8, 5.5);
    vertices[3].Set(   1,  10);
    vertices[4].Set(  -1,  10);
    vertices[5].Set(-2.8, 5.5);
    vertices[6].Set(  -3, 2.5);
    vertices[7].Set(-1.5,   0);
    b2PolygonShape polygonShape;
    polygonShape.Set( vertices, 8 );

    b2FixtureDef fixtureDef;
    fixtureDef.filter.groupIndex = m_spec.groupIndex;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 0.1f;

    b2Fixture* fixture = m_body->CreateFixture(&fixtureDef);

    //prepare common joint parameters
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = m_body;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;
    jointDef.upperAngle = 0;
    jointDef.localAnchorB.SetZero();//center of tire

    //back left tire
    CarTire* tire = new CarTire(m_spec.backLeftTire, m_world);
    tire->m_body->SetTransform(b2Vec2(-3.0f, 0.75f), 0.0f);
    jointDef.bodyB = tire->m_body;
    jointDef.localAnchorA.Set( -3, 0.75f );
    blJoint = (b2RevoluteJoint*)m_world->CreateJoint( &jointDef );
    m_tires.push_back(tire);

    //back right tire
    tire = new CarTire(m_spec.backRightTire, m_world);
    tire->m_body->SetTransform(b2Vec2(3.0f, 0.75f), 0.0f);
    jointDef.bodyB = tire->m_body;
    jointDef.localAnchorA.Set( 3, 0.75f );
    brJoint = (b2RevoluteJoint*)m_world->CreateJoint( &jointDef );
    m_tires.push_back(tire);

    //front left tire
    tire = new CarTire(m_spec.frontLeftTire, m_world);
    tire->m_body->SetTransform(b2Vec2(-3.0f, 8.5f), 0.0f);
    jointDef.bodyB = tire->m_body;
    jointDef.localAnchorA.Set( -3, 8.5f );
    flJoint = (b2RevoluteJoint*)m_world->CreateJoint( &jointDef );
    m_tires.push_back(tire);

    //front right tire
    tire = new CarTire(m_spec.frontRightTire, m_world);
    tire->m_body->SetTransform(b2Vec2(3.0f, 8.5f), 0.0f);
    jointDef.bodyB = tire->m_body;
    jointDef.localAnchorA.Set( 3, 8.5f );
    frJoint = (b2RevoluteJoint*)m_world->CreateJoint( &jointDef );
    m_tires.push_back(tire);

    for(int i = 0; i < m_tires.size(); i++)
        m_tires[i]->m_body->SetActive(m_active);

    // rayVision
    rayVision = new RayVision(m_spec.rayVision, m_world, m_body);
    rayVision->m_body->SetTransform(b2Vec2(0.0f, 8.5f), 180.0f * DEGTORAD);
    rayVision->setActive(m_active);
    // rayVision = new RayVision(m_world, 16, 50, 0x0000, true, true);

    b2WeldJointDef weldJointDef;
    weldJointDef.collideConnected = false;
    weldJointDef.bodyA = m_body; // car
    weldJointDef.localAnchorA.Set(0.0f, 8.5f);
    weldJointDef.bodyB = rayVision->m_body;
    weldJointDef.localAnchorB.Set(0.0f, 0.0f);
    weldJointDef.referenceAngle = 180 * DEGTORAD;
    rvJoint = (b2WeldJoint*)m_world->CreateJoint(&weldJointDef);

    m_body->SetUserData(this);
}

Car::~Car() {
    delete rayVision;
    for (int i = 0; i < m_tires.size(); i++)
        delete m_tires[i];

    b2Joint* joints[] = { blJoint, brJoint, flJoint, frJoint, rvJoint };
    for(int i = 0; i < 5; i++)
    {
        b2Joint* joint_list = m_world->GetJointList();
        while(joint_list != NULL)
        {
            if (joint_list == joints[i]) 
            {
                m_world->DestroyJoint(joints[i]);
                break;
            }
            joint_list = joint_list->GetNext();
        }
    }
}

void Car::setTransform(const b2Vec2& position, float angle) 
{
    m_body->SetTransform(position, angle);
    m_tires[0]->m_body->SetTransform(blJoint->GetAnchorA(), angle);
    m_tires[1]->m_body->SetTransform(brJoint->GetAnchorA(), angle);
    m_tires[2]->m_body->SetTransform(flJoint->GetAnchorA(), angle);
    m_tires[3]->m_body->SetTransform(frJoint->GetAnchorA(), angle);
    rayVision->m_body->SetTransform(rvJoint->GetAnchorA(), angle + 90.0f * DEGTORAD);
}

void Car::update(int controlState) {
    for (int i = 0; i < m_tires.size(); i++)
        m_tires[i]->updateFriction();
    for (int i = 0; i < m_tires.size(); i++)
        m_tires[i]->updateDrive(controlState);

    //control steering
    float lockAngle = 35 * DEGTORAD;
    float turnSpeedPerSec = 160 * DEGTORAD;//from lock to lock in 0.5 sec
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = 0;
    switch ( controlState & (CarTire::TDC_LEFT | CarTire::TDC_RIGHT) ) {
      case CarTire::TDC_LEFT:  desiredAngle = lockAngle;  break;
      case CarTire::TDC_RIGHT: desiredAngle = -lockAngle; break;
    default: ;//nothing
    }
    float angleNow = flJoint->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp( angleToTurn, -turnPerTimeStep, turnPerTimeStep );
    float newAngle = angleNow + angleToTurn;
    flJoint->SetLimits( newAngle, newAngle );
    frJoint->SetLimits( newAngle, newAngle );
}

// Checkpoint should be traversed in ascending order
void Car::updateCheckpoint(Checkpoint *chpoint) 
{
    if (!m_lastCheckpoint) 
    {
        m_lastCheckpoint = chpoint;
    } 
    else 
    {
        if (m_lastCheckpoint->getOrderNo() + 1 == chpoint->getOrderNo() ||
            (m_lastCheckpoint->getChpointType() == 1 && chpoint->getChpointType() == -1)) 
        {
            m_lastCheckpoint = chpoint;
            m_checkpointsNo++;

        }
    }
}

bool Car::setActive(bool active) {
    if (m_active != active) {
        m_active = active;
        
        m_body->SetActive(active);
        for(int i = 0; i < m_tires.size(); i++)
            m_tires[i]->setActive(active);
        rayVision->setActive(active);
    }
}

void Car::handleCollision(Entity* ent)
{
    // Entity::Type entType = ent->getType();
    EntType entType = ent->getType();

    // if (entType == Entity::Type::ENT_CHECKPOINT)
    if (entType == EntType::ENT_CHECKPOINT)
    {
        Checkpoint* chpoint = static_cast<Checkpoint*>(ent);  
        updateCheckpoint(chpoint);     
    }  
}