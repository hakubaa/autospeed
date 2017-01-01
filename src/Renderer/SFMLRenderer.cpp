
#include "Renderer/SFMLRenderer.h"


SFMLRenderer::SFMLRenderer(sf::RenderWindow* window, Camera* camera) : 
    m_window(window),
    m_camera(camera),
    m_fps(100)
{
}

SFMLRenderer::~SFMLRenderer() 
{
}

void SFMLRenderer::render(EntsBox *ents, SimMode* sim) { 
    m_window->clear(sf::Color::Black);
    m_window->setView(*m_camera);
    sim->getb2World()->DrawDebugData();
    m_window->display();  

    // FPS
    static sf::Clock fpsClock;
    static int framesNo = 0;

    framesNo++;
    if (framesNo > m_fps) // approximately update every second
    {
        m_fps = framesNo/fpsClock.getElapsedTime().asSeconds();
        framesNo = 0;
        fpsClock.restart();
    }
}