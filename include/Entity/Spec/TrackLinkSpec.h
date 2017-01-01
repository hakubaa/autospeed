#ifndef TRACKLINKDEF_H
#define TRACKLINKDEF_H

#include "Entity/Types.h"
#include "Entity/Spec/EntitySpec.h"
#include "tinyxml2.h"
#include <Box2D/Box2D.h>


class TrackLinkSpec : public EntitySpec {
    
public:

    b2Vec2 sNode;
    b2Vec2 eNode;
    bool isSensor;

public:
    TrackLinkSpec() : isSensor(false), sNode(0.0f, 0.0f), eNode(0.0f, 0.0f) { }
    tinyxml2::XMLElement* createXML(tinyxml2::XMLDocument* xmlDoc) const;
    void readXML(tinyxml2::XMLElement* node);

    EntType getType() const;
};

inline EntType TrackLinkSpec::getType() const
{
    return EntType::ENT_TRACKLINK;
}


#endif