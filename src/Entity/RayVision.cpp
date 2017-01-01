#include "Entity/RayVision.h"

RayVision::RayVision(RayVisionSpec spec, b2World* world, b2Body* parentBody) :
    Entity(world), 
    // m_world(world),
    m_spec(spec),
    m_parentBody(parentBody)
{ 
    // spread rays evenly
    m_rayVec = new b2Vec2[m_spec.n];
    float angle = 2*(float)abs(m_spec.maxRayAngle)/(float)(m_spec.n+1);
    float sAngle = -(float)abs(m_spec.maxRayAngle) + angle;
    for (int i = 0; i < m_spec.n; i++) {
        m_rayVec[i] = b2Vec2(sinf(sAngle * DEGTORAD), cosf(sAngle * DEGTORAD));
        sAngle += angle;
    }
        // m_rayVec[i] = b2Vec2(sinf((i+1) * angle * DEGTORAD), cosf((i+1) * angle * DEGTORAD));

    // body - source of rays visions
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    m_body = m_world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0001f;
    fixtureDef.filter.maskBits = 0x0000;

    b2CircleShape circleShape;
    circleShape.m_radius = 0.01f;
    circleShape.m_p.Set(0.0f, 0.0f);
    fixtureDef.shape = &circleShape;
    b2Fixture* fixture = m_body->CreateFixture(&fixtureDef);

    if (spec.showRays) {

        m_rayFixture = new b2Fixture*[m_spec.n];
        for(int i = 0; i < m_spec.n; i++) {
            b2EdgeShape rayShape;
            rayShape.Set(b2Vec2(0.0f, 0.0f), m_spec.length * b2Vec2(m_rayVec[i].x, -m_rayVec[i].y));
            fixtureDef.shape = &rayShape;
            m_rayFixture[i] = m_body->CreateFixture(&fixtureDef);
        }

    }

    m_body->SetUserData(this);

    output = new float[m_spec.n];
}

RayVision::~RayVision() { 
    //std::cout << "RayVision::~RayVision {" << std::endl;
//    m_body->GetWorld()->DestroyBody(m_body);
    delete []m_rayVec; 
    delete []output;
    //std::cout << "} RayVision::~RayVision" << std::endl;
}

void RayVision::update() 
{
    // only update when vision is active
    if (m_active) {

        b2Vec2 d = m_body->GetWorldVector(b2Vec2(0.0f, -1.0f));
        b2Vec2 d_n(-d.y, d.x);

        float det = d_n.x * d.y - d.x * d_n.y;

        for(int i = 0; i < m_spec.n; i++) {

            // a little bit of magic
            float x = (m_rayVec[i].x * d.y - m_rayVec[i].y * d.x)/det;
            float y = (m_rayVec[i].y * d_n.x - m_rayVec[i].x * d_n.y)/det;

            float len = sqrt(x*x + y*y);
            x = x/len;
            y = y/len;

            // Reset the output
            output[i] = 1;

            // Ray casting
            RayCallback ray(this, i);
            m_world->RayCast(&ray, m_body->GetPosition() + b2Vec2(x, y), 
                m_body->GetPosition() + m_spec.length*b2Vec2(x, y));

            // Adjust output
            output[i] *= m_spec.length;

            if (m_spec.showRays && m_spec.dynamicRays) {

                m_body->DestroyFixture(m_rayFixture[i]);

                b2EdgeShape rayShape;
                rayShape.Set(b2Vec2(0.0f, 0.0f), output[i] * b2Vec2(m_rayVec[i].x, -m_rayVec[i].y));

                b2FixtureDef fixtureDef;
                fixtureDef.density = 0.0001f;
                fixtureDef.filter.maskBits = 0x0000;
                fixtureDef.shape = &rayShape;
                m_rayFixture[i] = m_body->CreateFixture(&fixtureDef);

            }

        } // for(int i = 0; i < n_; i++)

    } // if (active_) 


    // update RayCastCallbacks


}

bool RayVision::setActive(bool active) {
    if (m_active != active) {
        m_active = active;
        m_body->SetActive(active);
    }
}

RayVision::RayCallback::RayCallback(RayVision* rv, int ray_no) : 
    m_rv(rv),
    m_ray_no(ray_no)
{ }

float32 RayVision::RayCallback::ReportFixture(b2Fixture* fixture, 
    const b2Vec2& point, const b2Vec2& normal, float32 fraction) 
{
    Entity* ent = (Entity*)(fixture->GetBody())->GetUserData(); 
    if (!ent)
        return 1;

    if ((ent->getType() & m_rv->m_spec.filter) == 0)
        return 1;

    if (m_rv->output[m_ray_no] > fraction) 
        m_rv->output[m_ray_no] = fraction;

    return fraction;
}    
