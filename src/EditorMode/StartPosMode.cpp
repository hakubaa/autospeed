#include "CarSim/EditorMode/StartPosMode.h"


StartPosMode::StartPosMode(TrackEditor* editor) : 
    m_editor(editor),
    m_activeEnt(nullptr),
    m_entsCount(0)
{ 
}

void StartPosMode::handleEvent(const sf::Event& event) 
{
     switch(event.type) 
     {
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
                        if (ent->getEntityType() == Entity::Type::ENT_STARTPOS) 
                            for (b2Fixture* f = (*body)->GetFixtureList(); f; f = f->GetNext()) 
                                if (f->TestPoint(b2MousePos)) 
                                    isOverlapping = true;

                }
                                    
                if (!isOverlapping) {
                    sf::Vector2i mPos = sf::Mouse::getPosition(*m_editor->m_window);
                    b2Vec2 b2MousePos = SFMLDebugDraw::SFVecToB2Vec(
                        m_editor->m_window->mapPixelToCoords(mPos, m_editor->m_window->getView()));

                    m_activeEnt = new StartPos(m_editor->m_world, b2MousePos, 0.0f, 12.0f, 8.0f, m_entsCount);
                }
            }

            if (event.mouseButton.button == sf::Mouse::Button::Right)
            {
                if (m_activeEnt != nullptr) 
                {
                    delete m_activeEnt;
                    m_activeEnt = nullptr;
                }
            }

            break;

        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Button::Left) 
            {
                if (m_activeEnt != nullptr) 
                {
                    m_editor->addEntity(m_activeEnt);
                    m_entsCount++;
                    m_activeEnt = nullptr;
                }
            }
            break;

        case sf::Event::MouseMoved:

            if (m_activeEnt != nullptr)
            {
                // Get current mouse position
                sf::Vector2i mPos(event.mouseMove.x, event.mouseMove.y);
                b2Vec2 b2MousePos = SFMLDebugDraw::SFVecToB2Vec(
                    m_editor->m_window->mapPixelToCoords(mPos, m_editor->m_window->getView())); 

                b2Vec2 v = b2MousePos - m_activeEnt->getPosition();
                v.Normalize();
                float angle = atan2(v.y, v.x); //acos(v.x);

                m_activeEnt->getMainBody()->SetTransform(m_activeEnt->getPosition(), angle);
            }

            break;

        default:
            break;
    }
}

void StartPosMode::update(sf::Time timeStep)
{
}

std::string StartPosMode::getStatus() const 
{
    std::stringstream s;
    s << "Start Pos.: count: " << m_entsCount;
    return s.str();
}

std::string StartPosMode::getInfo() const 
{
    return "";
}