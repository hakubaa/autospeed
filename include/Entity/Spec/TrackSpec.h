#ifndef TRACKSPEC_H
#define TRACKSPEC_H

#include "Entity/Spec/EntitySpec.h"
#include "Entity/Spec/CheckpointSpec.h"
#include "Entity/Spec/NodeSpec.h"
#include "Entity/Spec/TrackLinkSpec.h"
#include "Entity/Spec/StartPosSpec.h"

#include "tinyxml2.h"

#include <Box2D/Box2D.h>

#include <fstream>
#include <vector>

class TrackSpec {
    std::vector<EntitySpec*> m_spec;
    std::vector<StartPosSpec*> m_startpos;

public:
    TrackSpec() { }
    TrackSpec(const TrackSpec&);
    ~TrackSpec();
    
    TrackSpec& operator=(const TrackSpec&);
    
    void addEntity(EntitySpec* ent);
    // void delEntity(EntitySpec ent);

    StartPosSpec* getStartPos(int index) const;
    int startPosCount() const;

    tinyxml2::XMLDocument* createXML() const;
    tinyxml2::XMLError loadXML(tinyxml2::XMLDocument& xmlDoc);

    tinyxml2::XMLError save(const std::string& fileName) const;
    tinyxml2::XMLError load(const std::string& fileName);

    void clear();
    int size() const;
    EntitySpec* operator[](int index) const;
};

#endif