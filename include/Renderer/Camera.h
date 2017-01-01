#ifndef CAMERA_H
#define CAMERA_H

#include "Entity/Entity.h"

#include "SFMLDebugDraw.h"
#include "deg2rad.h"

#include "deg2rad.h"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <cmath>
#include <vector>
#include <iostream>

class Camera : public sf::View {

    bool moveWithMouse_;
    sf::Vector2i mouseInitPos_; // mouse's inital position when mouse was clicked
    sf::Vector2f cameraInitPos_;  // camera's inital position when mouse was clicekd

    Entity* trackedEntity_;

    sf::RenderWindow* window_;

    class CameraQueryCallback;
public:
    Camera(sf::RenderWindow* window) : window_(window), View(window->getView().getCenter(), 
        window->getView().getSize()), trackedEntity_(nullptr), moveWithMouse_(false) { }
    Camera(sf::RenderWindow* window, const sf::FloatRect& rectangle) : 
        window_(window), View(rectangle), moveWithMouse_(false), trackedEntity_(nullptr) { }
    Camera(sf::RenderWindow* window, const sf::Vector2f& center, const sf::Vector2f& size) : 
        window_(window), View(center, size), moveWithMouse_(false), trackedEntity_(nullptr) { }

    void trackEntity(Entity* ent) { trackedEntity_ = ent; }
    void stopTracking() { trackedEntity_ = nullptr; }

    void update();
    void handleEvent(const sf::Event& event, b2World* world);
};

#endif


/*
   54 
   61     explicit View(const FloatRect& rectangle);
   62 
   70     View(const Vector2f& center, const Vector2f& size);
   71 
   81     void setCenter(float x, float y);
   82 
   91     void setCenter(const Vector2f& center);
   92 
  102     void setSize(float width, float height);
  103 
  112     void setSize(const Vector2f& size);
  113 
  124     void setRotation(float angle);
  125 
  141     void setViewport(const FloatRect& viewport);
  142 
  153     void reset(const FloatRect& rectangle);
  154 
  163     const Vector2f& getCenter() const;
  164 
  173     const Vector2f& getSize() const;
  174 
  183     float getRotation() const;
  184 
  193     const FloatRect& getViewport() const;
  194 
  204     void move(float offsetX, float offsetY);
  205 
  214     void move(const Vector2f& offset);
  215 
  224     void rotate(float angle);
  225 
  241     void zoom(float factor);
  242 
  253     const Transform& getTransform() const;
  254 
  265     const Transform& getInverseTransform() const;


*/