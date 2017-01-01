#include "CarSim/EditorMode/CheckpointMode.h"

// STATIC VARIABLE INITIALIZATION
Checkpoint* CheckpointMode::m_lastCheckpoint = nullptr;
int CheckpointMode::m_type = 0;
int CheckpointMode::m_orderNo = 0;


CheckpointMode::CheckpointMode(TrackEditor* editor) : 
    m_editor(editor), 
    sNode(nullptr), 
    eNode(nullptr)
    { }

void CheckpointMode::handleEvent(const sf::Event& event) {

     switch(event.type) {

        case sf::Event::MouseButtonPressed:

            if (event.mouseButton.button == sf::Mouse::Button::Left) {
                
                sf::Vector2i mPos = sf::Mouse::getPosition(*m_editor->m_window);
                b2Vec2 b2MousePos = SFMLDebugDraw::SFVecToB2Vec(
                    m_editor->m_window->mapPixelToCoords(mPos, m_editor->m_window->getView()));

                Box2DQueryCallback queryCallback;
                b2AABB aabb;
                aabb.lowerBound = b2MousePos - b2Vec2(-0.01f, -0.01f);
                aabb.upperBound = b2MousePos + b2Vec2(0.01f, 0.01f);
                m_editor->m_world->QueryAABB(&queryCallback, aabb);

                for(std::vector<b2Body*>::iterator body = queryCallback.foundBodies.begin(); 
                    body != queryCallback.foundBodies.end(); ++body) {

                    Entity* ent = (Entity*)((*body)->GetUserData());
                    if (ent != nullptr) 
                        if (ent->getEntityType() == Entity::Type::ENT_NODE) 
                            for (b2Fixture* f = (*body)->GetFixtureList(); f; f = f->GetNext()) 
                                if (f->TestPoint(b2MousePos)) {
                                    if (sNode == nullptr) {
                                        sNode = (Node*)ent;
                                    } else {
                                        eNode = (Node*)ent;

                                        if (eNode != sNode) {
                                            Checkpoint* chpoint = new Checkpoint(m_editor->m_world, sNode->getPosition(),
                                                eNode->getPosition(), m_orderNo++, m_type);
                                            m_editor->addEntity(chpoint);
                                            m_lastCheckpoint = chpoint;
                                        
                                            sNode = nullptr;
                                            eNode = nullptr;
                                        } else {
                                            eNode = nullptr;
                                        }
                                    }

                                }
                }
            } 
            break;

        case sf::Event::KeyPressed:

            if (event.key.code == sf::Keyboard::Num1) 
                m_type = -1;
            if (event.key.code == sf::Keyboard::Num2) 
                m_type = 0;
            if (event.key.code == sf::Keyboard::Num3)
                m_type = 1;
            if (event.key.code == sf::Keyboard::R) {
                m_lastCheckpoint = nullptr;
                m_orderNo = 0;
                m_type = 0;
            }
            if (event.key.code == sf::Keyboard::U) {
                sNode = nullptr;
                eNode = nullptr;
            }

            break;

        default:
            break;
    }

}

void CheckpointMode::update(sf::Time timeStep)
{ 
}

std::string CheckpointMode::getStatus() const {
    std::stringstream s;

    s << "Checkpoint Mode: order no.: " << m_orderNo << "; type: " << m_type << "; ";
    if (sNode == nullptr) {
        s << "sNode: null; ";  
    } else {
        b2Vec2 pos = sNode->getPosition();
        s << "sNode: (" <<  pos.x << ", " << pos.y << "); "; 
    }

    if (eNode == nullptr){
        s << "eNode: null; ";  
    } else {
        b2Vec2 pos = eNode->getPosition();
        s << "eNode: (" << pos.x << ", " << pos.y << "); "; 
    }

    return s.str();
}

std::string CheckpointMode::getInfo() const {
    std::stringstream s;

    s << "Checkpoint Mode" << std::endl
      << "Type START  - 1" << std::endl 
      << "Type INNER  - 2" << std::endl
      << "Type FINISH - 3" << std::endl
      << "U(U)nselect node" << std::endl
      << "R(R)eset order" << std::endl;

    return s.str();
}