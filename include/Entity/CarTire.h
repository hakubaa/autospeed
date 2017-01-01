#ifndef CARTIRE_H
#define CARTIRE_H

#include "Entity/Types.h"
#include "Entity/Spec/CarTireSpec.h"
#include "Entity/Entity.h"
#include "Entity/FUD/FixtureUserData.h"
#include "Entity/FUD/CarTireFUD.h"
#include "Entity/FUD/GroundAreaFUD.h"

#include <iostream>
#include <set>

class Car;

class CarTire : public Entity 
{
    friend Car;

    CarTireSpec m_spec;
    
    //b2World* m_world;
    bool m_active;
    std::set<GroundAreaFUD*> m_groundAreas;
    float m_currentTraction;
    CarTireFUD* m_tireFUD;

public:

    enum {
        TDC_LEFT   = 0x1,
        TDC_RIGHT  = 0x2,
        TDC_UP     = 0x4,
        TDC_DOWN   = 0x8
    };

    //b2Body* m_body;

    CarTire(CarTireSpec spec, b2World* world);
    ~CarTire();

    b2Vec2 getLateralVelocity();
    b2Vec2 getForwardVelocity();

    void updateFriction();
    void updateDrive(int controlState);
    void updateTurn(int controlState);
    void addGroundArea(GroundAreaFUD* ga);
    void removeGroundArea(GroundAreaFUD* ga);
    void updateTraction();

    bool isActive() const;
    bool setActive(bool active);
       
    const b2Vec2& getPosition() const;
    EntType getType() const;
    //b2Body* getMainBody() const;
    const CarTireSpec& getSpec() const; 
};

inline EntType CarTire::getType() const
{
    return m_spec.getType();
}

#endif