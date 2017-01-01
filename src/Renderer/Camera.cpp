#include "Renderer/Camera.h"

 class Camera::CameraQueryCallback : public b2QueryCallback {
  public:
      std::vector<b2Body*> foundBodies;
      
      bool ReportFixture(b2Fixture* fixture) {
          foundBodies.push_back( fixture->GetBody() ); 
          return true;
      }
  };


void Camera::handleEvent(const sf::Event& event, b2World* world) 
{
     switch(event.type) {   

        case sf::Event::MouseWheelMoved:
            zoom(1.0f + event.mouseWheel.delta*0.1f);
            break;

       case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Button::Right) {
                moveWithMouse_ = true;
                mouseInitPos_ = sf::Mouse::getPosition(); 
                cameraInitPos_ = this->getCenter();
                
            } else if (event.mouseButton.button == sf::Mouse::Button::Left) {
                
                b2Vec2 b2MousePos = SFMLDebugDraw::SFVecToB2Vec(
                    window_->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), *this));

                CameraQueryCallback queryCallback;
                b2AABB aabb;
                aabb.lowerBound = b2MousePos - b2Vec2(-0.01f, -0.01f);
                aabb.upperBound = b2MousePos + b2Vec2(0.01f, 0.01f);
                world->QueryAABB(&queryCallback, aabb);

                for(std::vector<b2Body*>::iterator body = queryCallback.foundBodies.begin(); 
                    body != queryCallback.foundBodies.end(); ++body) {

                    Entity* ent = (Entity*)((*body)->GetUserData());
                    if (ent != nullptr) 
                        if (ent->getType() == EntType::ENT_CAR) 
                            for (b2Fixture* f = (*body)->GetFixtureList(); f; f = f->GetNext()) 
                                if (f->TestPoint(b2MousePos))
                                    trackedEntity_ = ent;
                    
                }
            } 
            break;

        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Button::Right) 
                moveWithMouse_ = false;
            break;

        default:
            break;
    }
}

void Camera::update() 
{

    if (moveWithMouse_) {
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        float sizeFactor = this->getSize().x/window_->getSize().x;
        sf::Vector2f offset(sizeFactor*(mousePos.x - mouseInitPos_.x), 
            sizeFactor*(mousePos.y - mouseInitPos_.y));
        float alfa = getRotation() * DEGTORAD;
        sf::Vector2f roffset(offset.x * cos(alfa) - offset.y * sin(alfa),
                             offset.x * sin(alfa) + offset.y * cos(alfa));
        this->move(-roffset);
        mouseInitPos_ = mousePos;

    } else if (trackedEntity_ != nullptr) {
        
        sf::Vector2f entPos = 
            SFMLDebugDraw::B2VecToSFVec(trackedEntity_->getPosition());
        sf::Vector2f offset(entPos.x - this->getCenter().x, entPos.y - this->getCenter().y);
        this->move(offset);

        // // rotation
        // b2Vec2 entForwardNormal = trackedEntity_->getEntityBody()->GetWorldVector(b2Vec2(1,0));
        // float det = entForwardNormal.x*0 - entForwardNormal.y*1;
        // float angle = std::atan2(det, b2Dot(entForwardNormal, b2Vec2(-1,0)));
        // this->setRotation(angle * RADTODEG);
    }

}