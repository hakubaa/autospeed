#include "Entity/CarTire.h"

CarTire::CarTire(CarTireSpec spec, b2World* world) : 
    Entity(world),
    m_spec(spec),
    // m_world(world),
    m_active(false) 
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    m_body = m_world->CreateBody(&bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox( 0.5f, 1.25f );

    b2FixtureDef fixtureDef;
    fixtureDef.filter.groupIndex = m_spec.groupIndex;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 1.0f;

    b2Fixture* fixture = m_body->CreateFixture(&fixtureDef);//shape density
    m_tireFUD = new CarTireFUD();
    fixture->SetUserData(m_tireFUD);
    m_body->SetUserData(this);

    m_currentTraction = 1;
}

CarTire::~CarTire() {
    delete m_tireFUD;
//    m_world->DestroyBody(m_body);
}

b2Vec2 CarTire::getLateralVelocity() {
    b2Vec2 currentRightNormal = m_body->GetWorldVector( b2Vec2(1,0) );
    return b2Dot( currentRightNormal, m_body->GetLinearVelocity() ) * currentRightNormal;
}

b2Vec2 CarTire::getForwardVelocity() {
    b2Vec2 currentForwardNormal = m_body->GetWorldVector(b2Vec2(0,1));
    return b2Dot(currentForwardNormal, m_body->GetLinearVelocity()) * currentForwardNormal;
}

void CarTire::updateFriction() {
    // std::cout << "updateFriction: m_currentTraction = " << m_currentTraction << std::endl;

    //lateral linear velocity
    b2Vec2 impulse = m_body->GetMass() * -getLateralVelocity();
    if ( impulse.Length() > m_spec.maxLateralImpulse )
        impulse *= m_spec.maxLateralImpulse / impulse.Length();
    m_body->ApplyLinearImpulse( m_currentTraction * impulse, m_body->GetWorldCenter(), true);

    //angular velocity
    m_body->ApplyAngularImpulse( m_currentTraction * 0.1f * m_body->GetInertia() * -m_body->GetAngularVelocity(), true );

    //forward linear velocity
    b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;
    m_body->ApplyForce( m_currentTraction * dragForceMagnitude * currentForwardNormal, m_body->GetWorldCenter(), true );
}

void CarTire::updateDrive(int controlState) {

    // std::cout << "updateDrive: m_currentTraction = " << m_currentTraction << std::endl;

    //find desired speed
    float desiredSpeed = 0;
    switch ( controlState & (TDC_UP|TDC_DOWN) ) {
        case TDC_UP:   desiredSpeed = m_spec.maxForwardSpeed;  break;
        case TDC_DOWN: desiredSpeed = m_spec.maxBackwardSpeed; break;
        default: return;//do nothing
    }

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = m_body->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot( getForwardVelocity(), currentForwardNormal );

    //apply necessary force
    float force = 0;
    if ( desiredSpeed > currentSpeed )
        force = m_spec.maxDriveForce;
    else if ( desiredSpeed < currentSpeed )
        force = -m_spec.maxDriveForce;
    else
        return;
    
    m_body->ApplyForce( m_currentTraction * force * currentForwardNormal, m_body->GetWorldCenter(), true );
}

void CarTire::updateTurn(int controlState) {
    float desiredTorque = 0;
    switch ( controlState & (TDC_LEFT|TDC_RIGHT) ) {
        case TDC_LEFT:  desiredTorque = 45;  break;
        case TDC_RIGHT: desiredTorque = -45; break;
        default: ;//nothing
    }
    m_body->ApplyTorque( desiredTorque, true );
}

void CarTire::addGroundArea(GroundAreaFUD* ga) { m_groundAreas.insert(ga); updateTraction(); }
void CarTire::removeGroundArea(GroundAreaFUD* ga) { m_groundAreas.erase(ga); updateTraction(); }
void CarTire::updateTraction() {
    if ( m_groundAreas.empty() )
        m_currentTraction = 1;
    else {
        //find area with highest traction
        m_currentTraction = 0;
        std::set<GroundAreaFUD*>::iterator it = m_groundAreas.begin();
        while (it != m_groundAreas.end()) {
            GroundAreaFUD* ga = *it;
            if ( ga->frictionModifier > m_currentTraction )
                m_currentTraction = ga->frictionModifier;
            ++it;
        }
    }
}

/*void setCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse) {
    m_maxForwardSpeed = maxForwardSpeed;
    m_maxBackwardSpeed = maxBackwardSpeed;
    m_maxDriveForce = maxDriveForce;
    m_maxLateralImpulse = maxLateralImpulse;
}*/

bool CarTire::isActive() const { return m_active; }
bool CarTire::setActive(bool active) {
    if (m_active != active) {
        m_active = active; 
        m_body->SetActive(active);
    }
}
   

const b2Vec2& CarTire::getPosition() const {
    return m_body->GetPosition();
}

// Entity::Type CarTire::getType() const {
//     return Entity::Type::ENT_CARTIRE;
// }

// inline b2Body* CarTire::getMainBody() const {
//     return m_body;
// }

const CarTireSpec& CarTire::getSpec() const {
    return m_spec;
}