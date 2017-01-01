#ifndef SFMLRENDERER_H
#define SFMLRENDERER_H

#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "Entity/EntsBox.h"

#include <Box2D/Box2D.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>

class SFMLRenderer : public Renderer {

    Camera* m_camera;
    sf::RenderWindow* m_window;
    
    float m_fps;

public:
    SFMLRenderer(sf::RenderWindow* window, Camera* camera);
    ~SFMLRenderer();

    void render(EntsBox *ents, SimMode* sim);
    float getFPS() const;
};

inline float SFMLRenderer::getFPS() const
{
    return m_fps;
}

#endif