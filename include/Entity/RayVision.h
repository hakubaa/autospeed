#ifndef RAYVISION_H
#define RAYVISION_H

#include "Entity/Types.h"
#include "Entity/Spec/RayVisionSpec.h"
#include "Entity/Entity.h"
#include "deg2rad.h"

#include <Box2D/Box2D.h>

#include <cmath>
#include <vector>
#include <iostream>
#include <cstdint>

class Car;

class RayVision : public Entity {

    friend Car;

    RayVisionSpec m_spec;

    bool m_active;
    //b2World* m_world;
    b2Body* m_parentBody;

    b2Vec2* m_rayVec; 
    b2Fixture** m_rayFixture;

    class RayCallback;
    friend RayCallback;
    class RayCallback : public b2RayCastCallback {
        int m_ray_no;
        RayVision* m_rv;
    public:
        RayCallback(RayVision* rv, int ray_no);
        float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) ;  
    };
    
public:

    float* output;
    //b2Body* m_body;

    RayVision(RayVisionSpec spec, b2World* world, b2Body* parentBody = nullptr);
    ~RayVision();

    int size() const;
    bool isActive() const;
    bool setActive(bool active);

    b2Vec2& operator [](const int index);
    const b2Vec2& getPosition() const;
    //b2Body* getMainBody() const;
    EntType getType() const;
    const RayVisionSpec& getSpec() const;

    void update();
    b2Vec2* getLastOutput();

};

inline int RayVision::size() const { 
    return m_spec.n; 
}

inline bool RayVision::isActive() const { return m_active; }

inline b2Vec2& RayVision::operator [](const int index) { 
    return m_rayVec[index];
}

inline const b2Vec2& RayVision::getPosition() const {
    return m_body->GetPosition();
}

// inline b2Body* RayVision::getMainBody() const {
//     return m_body;
// }

inline EntType RayVision::getType() const {
    return m_spec.getType();
}

inline const RayVisionSpec& RayVision::getSpec() const {
    return m_spec;
}

#endif