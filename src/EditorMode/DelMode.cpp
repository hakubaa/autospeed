#include "CarSim/EditorMode/DelMode.h"

DelMode::DelMode(TrackEditor* editor) : m_editor(editor) { }

void DelMode::handleEvent(const sf::Event& event) {

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

                    if (ent != nullptr) {
                        std::vector<Entity*>::iterator it = std::find(m_editor->ents.begin(), m_editor->ents.end(), ent);
                        if (it != m_editor->ents.end())
                            m_editor->m_world->DestroyBody(*body);
                            m_editor->ents.erase(it);
                    }
                            
                }
            } 
            break;

        default:
            break;
    }

}

void DelMode::update(sf::Time timeStep)
{ 
}

std::string DelMode::getStatus() const {
    std::stringstream s;

    return s.str();
}

std::string DelMode::getInfo() const {
    std::stringstream s;

    return s.str();
}