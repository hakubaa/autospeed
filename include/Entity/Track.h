#ifndef TRACK_H
#define TRACK_H

#include "Entity/Spec/TrackSpec.h"

#include "Entity/Entity.h"
#include "Entity/Node.h"
#include "Entity/Checkpoint.h"
#include "Entity/TrackLink.h"
#include "Entity/StartPos.h"

#include <Box2D/Box2D.h>

#include <vector>

class Track {
    std::vector<Entity*> m_ents;
public:
    Track(const TrackSpec& spec, b2World* world);
    ~Track();
};

#endif