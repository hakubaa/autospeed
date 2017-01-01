#ifndef ENTITYDEF_H
#define ENTITYDEF_H

#include "Entity/Types.h"
#include "tinyxml2.h"

class EntitySpec {

public:
    virtual ~EntitySpec() { }
    virtual tinyxml2::XMLElement* createXML(tinyxml2::XMLDocument*) const { return nullptr; }
    virtual void readXML(tinyxml2::XMLElement*) { }
    virtual EntType getType() const { return EntType::ENT_NONE; }
};

#endif