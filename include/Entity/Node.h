#ifndef NODE_H
#define NODE_H

#include "Entity/Spec/NodeSpec.h"
#include "Entity/Entity.h"
#include "Entity/Types.h"

#include <Box2D/Box2D.h>

#include <vector>
#include <algorithm>


class Node : public Entity {
    
    //b2World* m_world;    
    NodeSpec m_spec;

public:
    //b2Body* m_body;

    Node(NodeSpec spec, b2World* world);
    ~Node();

    const b2Vec2& getPosition() const;
    //b2Body* getMainBody() const;
    EntType getType() const;
    const NodeSpec& getSpec() const;
};

inline EntType Node::getType() const
{
    return m_spec.getType();
}

#endif