#include "CarSim/EditorMode/LinkMode.h"

LinkMode::LinkMode(TrackEditor* editor) : m_editor(editor), sNode(nullptr), eNode(nullptr) { }

void LinkMode::handleEvent(const sf::Event& event) {

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
                                            TrackLink *link = new TrackLink(m_editor->m_world, sNode->getPosition(),
                                                eNode->getPosition(), false);
                                            m_editor->addEntity(link);

                                            sNode = eNode;
                                            eNode = nullptr;
                                        } else {
                                            eNode = nullptr;
                                        }
                                    }

                                }
                }
            } 
            break;

        default:
            break;
    }

}

void LinkMode::update(sf::Time timeStep)
{ 
}

std::string LinkMode::getStatus() const {
    std::stringstream s;

    return s.str();
}

std::string LinkMode::getInfo() const {
    std::stringstream s;

    return s.str();
}