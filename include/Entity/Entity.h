#ifndef ENTITY_H
#define ENTITY_H

#include "Entity/Spec/EntitySpec.h"
#include "Entity/Types.h"

#include <cstdint>
#include <Box2D/Box2D.h>
#include <iostream>

class Entity 
{
protected:
    b2Body* m_body;
    b2World* m_world;

public:
    Entity(b2World* world) : m_world(world), m_body(nullptr) { }
    virtual ~Entity() 
    { 
        // destory main body
        if (m_body != nullptr)
        {
            b2Body* body_list = m_world->GetBodyList();
            while (body_list != NULL)
            {
                if (body_list == m_body)
                {
                    m_world->DestroyBody(m_body);
                    break;
                }
                body_list = body_list->GetNext();
            }
        }
    }

    virtual const b2Vec2& getPosition() const = 0;
    //virtual b2Body* getMainBody() { return m_body; }
    virtual EntType getType() const = 0;
    virtual const EntitySpec& getSpec() const = 0;
    virtual void handleCollision(Entity* ent) { }
};


#endif