#ifndef NODEDEF_H
#define NODEDEF_H

#include "Entity/Types.h"
#include "Entity/Spec/EntitySpec.h"
#include "tinyxml2.h"

#include <Box2D/Box2D.h>

class NodeSpec : public EntitySpec 
{
public:

    float radius;
    b2Vec2 pos;

    NodeSpec() : radius(0.0f), pos(b2Vec2(0.0f, 0.0f)) { }

    tinyxml2::XMLElement* createXML(tinyxml2::XMLDocument* xmlDoc) const;
    void readXML(tinyxml2::XMLElement*);

    EntType getType() const;
};

inline EntType NodeSpec::getType() const
{
    return EntType::ENT_NODE;
}

#endif