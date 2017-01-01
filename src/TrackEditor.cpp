#include "CarSim/TrackEditor.h"


TrackEditor::TrackEditor(sf::RenderWindow* window, b2World* world) : m_window(window), 
    m_world(world), m_activeNode(nullptr) {

    m_mode = new LazyMode(this);

}

TrackEditor::~TrackEditor() {
    for(int i = 0; i < ents.size(); i++)
        delete ents[i];
    ents.clear();
    delete m_mode;
}

void TrackEditor::addEntity(Entity* ent) {
    ents.push_back(ent);
}

void TrackEditor::delEntity(Entity* ent) {
    std::vector<Entity*>::iterator it = std::find(ents.begin(), ents.end(), ent);
    if (it != ents.end())
        ents.erase(it);
}

void TrackEditor::handleEvent(const sf::Event& event) {

    switch (event.type) {

        case sf::Event::KeyPressed:

            switch(event.key.code) {

                case sf::Keyboard::N:
                    delete m_mode;
                    m_mode = new NodeMode(this);
                    break;

                case sf::Keyboard::T:
                    delete m_mode;
                    m_mode = new LinkMode(this);
                    break;

                case sf::Keyboard::D:
                    delete m_mode;
                    m_mode = new DelMode(this);
                    break;

                case sf::Keyboard::L:
                    delete m_mode;
                    m_mode = new LazyMode(this);
                    break;

                case sf::Keyboard::C:
                    delete m_mode;
                    m_mode = new CheckpointMode(this);
                    break;

                case sf::Keyboard::S:
                    delete m_mode;
                    m_mode = new StartPosMode(this);
                    break;                

                default:
                    break;
            }

            if (event.key.code == sf::Keyboard::F2)
            {
                std::string fileName = FileChooser::getFileName(Gtk::FILE_CHOOSER_ACTION_SAVE);  
                tinyxml2::XMLDocument* xmlDoc = createXML();
                tinyxml2::XMLError eResult = xmlDoc->SaveFile(fileName.c_str()); 
                delete xmlDoc; 
            }   

            if (event.key.code == sf::Keyboard::F4) 
            {
                std::string fileName = FileChooser::getFileName(Gtk::FILE_CHOOSER_ACTION_OPEN);  
                tinyxml2::XMLDocument xmlDoc;
                tinyxml2::XMLError eResult = xmlDoc.LoadFile(fileName.c_str());
                loadXML(xmlDoc);
            }

            break;

        default:
            break;

    }

    m_mode->handleEvent(event);
}

std::string TrackEditor::getInfo() const {
    return m_mode->getInfo();
}

std::string TrackEditor::getStatus() const {
    return m_mode->getStatus();
}

tinyxml2::XMLDocument* TrackEditor::createXML() 
{
    using namespace tinyxml2;

    XMLDocument* xmlDoc = new XMLDocument();
    XMLNode * pRoot = xmlDoc->NewElement("Track");
    xmlDoc->InsertFirstChild(pRoot);

    for(std::vector<Entity*>::iterator ent = ents.begin(); ent != ents.end(); ++ent)
        pRoot->InsertEndChild((*ent)->getDef()->createXML(xmlDoc));

    return xmlDoc;

}

tinyxml2::XMLError TrackEditor::loadXML(tinyxml2::XMLDocument& xmlDoc) 
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

        std::cout << "Reading " << entType << " ... " << std::endl;

        Entity* ent = nullptr;

        if (entType == "ENT_NODE") 
        {
             NodeDef entDef;
             entDef.readXML(pEntity);
             entDef.world = m_world;
             ent = new Node(entDef);
        } 
        else if (entType == "ENT_TRACKLINK") 
        {
            TrackLinkDef entDef;
            entDef.readXML(pEntity);
            entDef.world = m_world;
            ent = new TrackLink(entDef);
        }
        else if (entType == "ENT_CHECKPOINT")
        {
            CheckpointDef entDef;
            entDef.readXML(pEntity);
            entDef.world = m_world;
            ent = new Checkpoint(entDef);
        }
        else if (entType == "ENT_STARTPOS")
        {
            StartPosDef entDef;
            entDef.readXML(pEntity);
            entDef.world = m_world;
            ent = new StartPos(m_world, entDef);
        }

        if (ent != nullptr)
            ents.push_back(ent);


        pEntity = pEntity->NextSiblingElement("Entity");
    }

    return XML_SUCCESS;
}


void TrackEditor::update(sf::Time timeStep) 
{
    m_mode->update(timeStep); 
}