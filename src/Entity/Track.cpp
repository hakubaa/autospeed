#include "Entity/Track.h"

Track::Track(const TrackSpec& spec, b2World* world)
{
    for(int i = 0; i < spec.size(); i++)
    {
        Entity* ent = nullptr;
        switch(spec[i]->getType())
        {
            case EntType::ENT_NODE:
                ent = new Node(*static_cast<NodeSpec*>(spec[i]), world);
                break;

            case EntType::ENT_TRACKLINK:
                ent = new TrackLink(*static_cast<TrackLinkSpec*>(spec[i]), world);
                break;

            case EntType::ENT_CHECKPOINT:
                ent = new Checkpoint(*static_cast<CheckpointSpec*>(spec[i]), world);
                break;

            case EntType::ENT_STARTPOS:
                ent = new StartPos(*static_cast<StartPosSpec*>(spec[i]), world);
                break;

            default:
                break;
        }
        if (ent != nullptr)
            m_ents.push_back(ent);
    }
}


Track::~Track()
{
    for(int i = 0; i < m_ents.size(); i++)
        delete m_ents[i];
    m_ents.clear();
}