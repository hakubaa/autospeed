#ifndef CHECKPOINTDEF_H
#define CHECKPOINTDEF_H

#include "Entity/Types.h"
#include "Entity/Spec/EntitySpec.h"
#include "tinyxml2.h"

#include <Box2D/Box2D.h>

class CheckpointSpec : public EntitySpec {
    
public:

    b2Vec2 sNode;
    b2Vec2 eNode;
    bool isSensor;
    int type;
    int orderNo;

public:
    CheckpointSpec();

    tinyxml2::XMLElement* createXML(tinyxml2::XMLDocument* xmlDoc) const;
    void readXML(tinyxml2::XMLElement* node);

    EntType getType() const;
};

inline EntType CheckpointSpec::getType() const
{
    return EntType::ENT_CHECKPOINT;
}


#endif