#ifndef TRACK_H
#define TRACK_H

#include "Entity/Spec/EntitySpec.h"
#include "Entity/Spec/CheckpointSpec.h"
#include "Entity/Spec/NodeSpec.h"
#include "Entity/Spec/TrackLinkSpec.h"
#include "Entity/Spec/StartPosSpec.h"
#include "Entity/Entity.h"
#include "Entity/Node.h"
#include "Entity/Checkpoint.h"
#include "Entity/TrackLink.h"
#include "Entity/StartPos.h"
#include "tinyxml2.h"

#include <Box2D/Box2D.h>

#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>


class Track {
    std::vector<Entity*> m_ents;
    std::vector<StartPos*> m_startPos;
    b2World* m_world;

    Track(const Track&);
public:
    Track(b2World* world);
    ~Track();

    void addEntity(Entity* ent);
    void delEntity(Entity* ent);

    StartPos* getStartPos(int index) const;
    int startPosCount() const;

    tinyxml2::XMLDocument* createXML() const;
    tinyxml2::XMLError loadXML(tinyxml2::XMLDocument& xmlDoc);

    void saveTrack(const std::string& fileName) const;
    void loadTrack(const std::string& fileName);

    static Track* loadTrack(const std::string& fileName, b2World* world);
};

#endif