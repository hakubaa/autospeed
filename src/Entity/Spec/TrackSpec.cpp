#include "Entity/Spec/TrackSpec.h"

TrackSpec::~TrackSpec()
{
    clear();
}

TrackSpec::TrackSpec(const TrackSpec& ts)
{
    for(int i = 0; i < ts.m_spec.size(); i++)
    {
        EntitySpec* ent = nullptr;
        switch(ts.m_spec[i]->getType())
        {
            case EntType::ENT_NODE:
                ent = new NodeSpec(*static_cast<NodeSpec*>(ts.m_spec[i]));
                break;
            case EntType::ENT_TRACKLINK:
                ent = new TrackLinkSpec(*static_cast<TrackLinkSpec*>(ts.m_spec[i]));
                break;
            case EntType::ENT_CHECKPOINT:
                ent = new CheckpointSpec(*static_cast<CheckpointSpec*>(ts.m_spec[i]));
                break;
            case EntType::ENT_STARTPOS:
                ent = new StartPosSpec(*static_cast<StartPosSpec*>(ts.m_spec[i]));
                break;
            default:
                break;
        }
        if (ent != nullptr)
        {
            m_spec.push_back(ent);
            if (ts.m_spec[i]->getType() == EntType::ENT_STARTPOS)
                m_startpos.push_back(static_cast<StartPosSpec*>(ent));
        }
    }
}

TrackSpec& TrackSpec::operator=(const TrackSpec& ts) 
{
    if (this != &ts)
    {
        clear();

        for(int i = 0; i < ts.m_spec.size(); i++)
        {
            EntitySpec* ent = nullptr;
            switch(ts.m_spec[i]->getType())
            {
                case EntType::ENT_NODE:
                    ent = new NodeSpec(*static_cast<NodeSpec*>(ts.m_spec[i]));
                    break;
                case EntType::ENT_TRACKLINK:
                    ent = new TrackLinkSpec(*static_cast<TrackLinkSpec*>(ts.m_spec[i]));
                    break;
                case EntType::ENT_CHECKPOINT:
                    ent = new CheckpointSpec(*static_cast<CheckpointSpec*>(ts.m_spec[i]));
                    break;
                case EntType::ENT_STARTPOS:
                    ent = new StartPosSpec(*static_cast<StartPosSpec*>(ts.m_spec[i]));
                    break;
                default:
                    break;
            }
            if (ent != nullptr)
            {
                m_spec.push_back(ent);
                if (ts.m_spec[i]->getType() == EntType::ENT_STARTPOS)
                    m_startpos.push_back(static_cast<StartPosSpec*>(ent));
            }
        }

    }
    return *this;   
}

void TrackSpec::addEntity(EntitySpec* ent) {
    m_spec.push_back(ent);
}

void TrackSpec::clear()
{
    for(int i = 0; i < m_spec.size(); i++) 
        delete m_spec[i];
    m_spec.clear();    
    m_startpos.clear(); 
}

// void TrackSpec::delEntity(EntitySpec ent) {
//     std::vector<EntitySpec>::iterator it = std::find(m_spec.begin(), m_spec.end(), ent);
//     if (*t != m_spec.end())
//         m_spec.erase(*it);    
// }

tinyxml2::XMLDocument* TrackSpec::createXML() const
{
    using namespace tinyxml2;

    XMLDocument* xmlDoc = new XMLDocument();
    XMLNode * pRoot = xmlDoc->NewElement("Track");
    xmlDoc->InsertFirstChild(pRoot);

    for(std::vector<EntitySpec*>::const_iterator ent = m_spec.begin(); ent != m_spec.end(); ++ent)
        pRoot->InsertEndChild((*ent)->createXML(xmlDoc));

    return xmlDoc;

}

tinyxml2::XMLError TrackSpec::save(const std::string& fileName) const {
    tinyxml2::XMLDocument* xmlDoc = createXML();
    tinyxml2::XMLError eResult = xmlDoc->SaveFile(fileName.c_str()); 
    delete xmlDoc;  
    return eResult;  
}


tinyxml2::XMLError TrackSpec::loadXML(tinyxml2::XMLDocument& xmlDoc) 
{   
    using namespace tinyxml2;

    XMLNode* pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr) 
        return XML_ERROR_FILE_READ_ERROR;
    
    XMLElement* pEntity = pRoot->FirstChildElement("Entity");

    while (pEntity != nullptr) 
    {
        const char* temp = nullptr;
        temp = pEntity->Attribute("type");
        if (temp == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
        std::string entType = temp;

        EntitySpec* ent = nullptr;
        
        if (entType == "ENT_NODE")
            ent = new NodeSpec;
        else if (entType == "ENT_TRACKLINK")
            ent = new TrackLinkSpec;
        else if (entType == "ENT_CHECKPOINT")
            ent = new CheckpointSpec;
        else if (entType == "ENT_STARTPOS")
            ent = new StartPosSpec;

        ent->readXML(pEntity);
        if (ent != nullptr)
        {
            m_spec.push_back(ent);
            if (entType == "ENT_STARTPOS")
                m_startpos.push_back(static_cast<StartPosSpec*>(ent));
        }

        pEntity = pEntity->NextSiblingElement("Entity");
    }

    return XML_SUCCESS;
}

tinyxml2::XMLError TrackSpec::load(const std::string& fileName) {
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError eResult = xmlDoc.LoadFile(fileName.c_str());
    if (eResult == tinyxml2::XML_SUCCESS) 
        loadXML(xmlDoc);
    return eResult;
}

int TrackSpec::startPosCount() const 
{
    return m_startpos.size();
}

StartPosSpec* TrackSpec::getStartPos(int index) const
{
    return m_startpos[index];
}

int TrackSpec::size() const 
{
    return m_spec.size();
}

EntitySpec* TrackSpec::operator[](int index) const
{
    if (index < m_spec.size())
        return m_spec[index];
    else
        return nullptr;
}