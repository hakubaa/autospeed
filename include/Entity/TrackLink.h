#ifndef TRACKLINK_H
#define TRACKLINK_H

#include "Entity/Types.h"
#include "Entity/Spec/TrackLinkSpec.h"
#include "Entity/Entity.h"

#include <Box2D/Box2D.h>


class TrackLink : public Entity 
{
    TrackLinkSpec m_spec;

    bool m_isSensor;
    //b2World* m_world;
    b2Fixture* m_tlFixture;

public:
    //b2Body* m_body;

public:
    TrackLink(TrackLinkSpec spec, b2World* world);
    ~TrackLink();

    const b2Vec2& getPosition() const;
    //b2Body* getMainBody() const;
    EntType getType() const;
    const TrackLinkSpec& getSpec() const;

    void setSensor(bool isSensor);
};

inline EntType TrackLink::getType() const
{
    return m_spec.getType();
}


#endif