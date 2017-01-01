#ifndef STARTPOSSPEC_H
#define STARTPOSSPEC_H

#include "Entity/Types.h"
#include "Entity/Spec/EntitySpec.h"

#include "tinyxml2.h"

#include <Box2D/Box2D.h>
#include <iostream>

class StartPosSpec : public EntitySpec 
{
public:

    float angle;
    b2Vec2 pos;
    float width;
    float height;
    int id;

    StartPosSpec() : angle(0.0f), pos(b2Vec2(0.0f, 0.0f)), 
        width(0.0f), height(0.0f), id(-1) { }

    tinyxml2::XMLElement* createXML(tinyxml2::XMLDocument* xmlDoc) const;
    void readXML(tinyxml2::XMLElement*);

    EntType getType() const;
};

inline EntType StartPosSpec::getType() const 
{
    return EntType::ENT_STARTPOS;
}

#endif