    #include "Track.h"

Track::Track(b2World* world) : m_world(world) { }

Track::~Track() {
    for(int i = 0; i < m_ents.size(); i++) 
        delete m_ents[i];
    m_ents.clear();
}

void Track::addEntity(Entity* ent) {
    m_ents.push_back(ent);
}

void Track::delEntity(Entity* ent) {
    std::vector<Entity*>::iterator it = std::find(m_ents.begin(), m_ents.end(), ent);
    if (it != m_ents.end())
        m_ents.erase(it);    
}

tinyxml2::XMLDocument* Track::createXML() const
{
    using namespace tinyxml2;

    XMLDocument* xmlDoc = new XMLDocument();
    XMLNode * pRoot = xmlDoc->NewElement("Track");
    xmlDoc->InsertFirstChild(pRoot);

    for(std::vector<Entity*>::const_iterator ent = m_ents.begin(); ent != m_ents.end(); ++ent)
        pRoot->InsertEndChild((*ent)->getSpec().createXML(xmlDoc));

    return xmlDoc;

}

void Track::saveTrack(const std::string& fileName) const {
    tinyxml2::XMLDocument* xmlDoc = createXML();
    tinyxml2::XMLError eResult = xmlDoc->SaveFile(fileName.c_str()); 
    if (eResult != tinyxml2::XML_SUCCESS) {
        std::cout << "Writing Track Error" << std::endl;
    }
    delete xmlDoc;    
}


tinyxml2::XMLError Track::loadXML(tinyxml2::XMLDocument& xmlDoc) 
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

        //std::cout << "Reading " << entType << " ... " << std::endl;

        Entity* ent = nullptr;

        if (entType == "ENT_NODE") 
        {
             NodeSpec entSpec;
             entSpec.readXML(pEntity);
             ent = new Node(entSpec, m_world);
        } 
        else if (entType == "ENT_TRACKLINK") 
        {
            TrackLinkSpec entSpec;
            entSpec.readXML(pEntity);
            ent = new TrackLink(entSpec, m_world);
        }
        else if (entType == "ENT_CHECKPOINT")
        {
            CheckpointSpec entSpec;
            entSpec.readXML(pEntity);
            ent = new Checkpoint(entSpec, m_world);
        }
        else if (entType == "ENT_STARTPOS")
        {
            StartPosSpec entSpec;
            entSpec.readXML(pEntity);
            ent = new StartPos(entSpec, m_world);
            if (ent != nullptr)
                m_startPos.push_back((StartPos*)ent);
        }

        if (ent != nullptr)
            m_ents.push_back(ent);


        pEntity = pEntity->NextSiblingElement("Entity");
    }

    return XML_SUCCESS;
}

void Track::loadTrack(const std::string& fileName) {
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError eResult = xmlDoc.LoadFile(fileName.c_str());
    if (eResult == tinyxml2::XML_SUCCESS) {
        loadXML(xmlDoc);
    } else {
        std::cout << "Track::loadTrack ERROR" << std::endl;
    }
}

Track* Track::loadTrack(const std::string& fileName, b2World* world) {
    Track* track = new Track(world);
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError eResult = xmlDoc.LoadFile(fileName.c_str());
    if (eResult == tinyxml2::XML_SUCCESS) {
        track->loadXML(xmlDoc);
    } else {
        std::cout << "Track::loadTrack ERROR" << std::endl;
    }
    return track;
}

int Track::startPosCount() const 
{
    return m_startPos.size();
}

StartPos* Track::getStartPos(int index) const
{
    return m_startPos[index];
}