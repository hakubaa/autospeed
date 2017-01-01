#include "Entity/TrackLine.h"

TrackLine::TrackLine(b2World* world, bool isSensor) : 
    m_world(world), 
    m_isSensor(isSensor) 
{ }

TrackLine::~TrackLine() 
{
    for(int i = 0; i < tls.size(); i++)
        delete tls[i];
}

void TrackLine::addNode(const b2Vec2& node) 
{
    tNodes.push_back(node);

    int n = tNodes.size();
    if (n > 1) {    // at least two points requried to create TrackLink
        b2Vec2 tlCenter = 0.5 * (tNodes[n-2] + tNodes[n-1]);
        TrackLinkSpec tlSpec;
        tlSpec.sNode = tNodes[n-2] - tlCenter;
        tlSpec.eNode = tNodes[n-1] - tlCenter;
        tlSpec.isSensor = m_isSensor;
        TrackLink* tl = new TrackLink(tlSpec, m_world);
        tl->m_body->SetTransform(tlCenter, tl->m_body->GetAngle());
        tls.push_back(tl);
    }
}

void TrackLine::SetSensor(bool isSensor) 
{
    if (m_isSensor != isSensor) {
        m_isSensor = isSensor;
        for(std::vector<TrackLink*>::iterator tl = tls.begin(); tl != tls.end(); ++tl)
            (*tl)->setSensor(m_isSensor);
    }
}