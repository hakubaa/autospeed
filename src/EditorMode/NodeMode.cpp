#include "CarSim/EditorMode/NodeMode.h"

NodeMode::NodeMode(TrackEditor* editor) : m_editor(editor) { }

void NodeMode::handleEvent(const sf::Event& event) {

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

                bool isOverlapping = false;
                for(std::vector<b2Body*>::iterator body = queryCallback.foundBodies.begin(); 
                    body != queryCallback.foundBodies.end(); ++body) {

                    Entity* ent = (Entity*)((*body)->GetUserData());
                    if (ent != nullptr) 
                        if (ent->getEntityType() == Entity::Type::ENT_NODE) 
                            for (b2Fixture* f = (*body)->GetFixtureList(); f; f = f->GetNext()) 
                                if (f->TestPoint(b2MousePos)) 
                                    isOverlapping = true;

                }
                                    
                if (!isOverlapping) {
                    sf::Vector2i mPos = sf::Mouse::getPosition(*m_editor->m_window);
                    b2Vec2 b2MousePos = SFMLDebugDraw::SFVecToB2Vec(
                        m_editor->m_window->mapPixelToCoords(mPos, m_editor->m_window->getView()));

                    Node* node = new Node(m_editor->m_world, 0.5f);
                    node->m_body->SetTransform(b2MousePos, node->m_body->GetAngle());
                    m_editor->addEntity(node);
                }
            }

            break;

        default:
            break;
    }

}

void NodeMode::update(sf::Time timeStep)
{ 
}

std::string NodeMode::getStatus() const {
    std::stringstream s;

    return s.str();
}

std::string NodeMode::getInfo() const {
    std::stringstream s;

    return s.str();
}