#ifndef TRACKLINE_H
#define TRACKLINE_H

#include "Entity/Spec/TrackLinkSpec.h"
#include "Entity/TrackLink.h"

#include <Box2D/Box2D.h>
#include <vector>

class TrackLine {

    b2World* m_world;
    bool m_isSensor;

    std::vector<b2Vec2> tNodes;
    std::vector<TrackLink*> tls;

public:
    TrackLine(b2World* world, bool isSensor);
    ~TrackLine();

    void addNode(const b2Vec2& node);
    void SetSensor(bool isSensor);
};

#endif