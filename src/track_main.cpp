
#include "CarSim/TrackEditor.h"
#include "CarSim/Camera.h"
#include "CarSim/Entity/TDCar.h"
#include "CarSim/Entity/TrackLine.h"
#include "CarSim/Entity/TrackLink.h"
#include "CarSim/Entity/Cube.h"
#include "CarSim/Entity/Node.h"
#include "CarSim/Entity/Checkpoint.h"
#include "CarSim/Entity/EntsColListener.h"

#include "SFMLDebugDraw.h"
#include "deg2rad.h"

#include <Box2D/Box2D.h>

#include <iostream>
#include <ctime>


int main (int argc, char* argv[]) {

    // Create important objects
    b2World world(b2Vec2(0.0f, 0.0f));
    const int velocityIterations = 6;
    const int positionIterations = 2;

    // Create window for renderer
    sf::RenderWindow window(sf::VideoMode(1366, 768), "AutoSpeed Learning Simulator", 
        sf::Style::Default);
    window.setPosition(sf::Vector2i(10, 10));
        
    SFMLDebugDraw debugDraw(window);
    debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
    world.SetDebugDraw(&debugDraw);

    Camera camera(&window);

    TrackEditor trackEditor(&window, &world);

    //################################################################################
    // Body Section
    //################################################################################

    TDCarDef carDef;
    carDef.world = &world;
    carDef.pos = b2Vec2(0.0f, 0.0f);
    carDef.angle = -90.0f * DEGTORAD;
    carDef.groupIndex = -1;
    carDef.rayVision.world = &world;
    carDef.rayVision.n = 16;
    carDef.rayVision.length = 80;
    carDef.rayVision.showRays = true;
    carDef.rayVision.dynamicRays = true;
    carDef.rayVision.maxRayAngle = 70;
    carDef.rayVision.filter = Entity::Type::ENT_TRACKLINK | Entity::Type::ENT_CUBE;
    carDef.tireDef.world = &world;
    carDef.tireDef.groupIndex = -1;

    // Create my own car
    TDCar car(carDef);
    car.setActive(true);

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/X11/Type1/c0419bt_.pfb");

    sf::Text infoText;
    infoText.setCharacterSize(16);
    infoText.setColor(sf::Color::Red);
    infoText.setFont(font);

    sf::Text statusText;
    statusText.setCharacterSize(16);
    statusText.setColor(sf::Color::Red);
    statusText.setFont(font);

    //################################################################################

    const sf::Time TIME_STEP = sf::seconds(0.01f);
    sf::Time accumulator = sf::seconds(0.0f);
    sf::Clock updateClock;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
             switch(event.type) {

                case sf::Event::Closed:
                    window.close();
                    break;            

                default:
                    break;
            }
            camera.handleEvent(event, &world);
            trackEditor.handleEvent(event);
        }

        accumulator += updateClock.restart();
        while (accumulator > TIME_STEP) {

            trackEditor.update(TIME_STEP);

            int controlState = 0;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                controlState |= TDTire::TDC_RIGHT;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                controlState |= TDTire::TDC_LEFT;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                controlState |= TDTire::TDC_UP;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                controlState |= TDTire::TDC_DOWN;        

            car.rayVision->update();
            car.update(controlState);   
            
            camera.update();
            world.Step(TIME_STEP.asSeconds(), velocityIterations, positionIterations);

            // Update info and status

            std::stringstream info;
            info << "N(N)ode Mode" << std::endl
                 << "T(T)rack Link Mode" << std::endl
                 << "L(L)azy Mode" << std::endl
                 << "C(C)heckpoint Mode" << std::endl
                 << "S(S)tarting Pos. Mode" << std::endl
                 << "D(D)elete Mode" << std::endl
                 << std::endl
                 << "Save - F2" << std::endl
                 << "Load - F4"
                 << std::endl << std::endl
                 << trackEditor.getInfo();
            infoText.setString(info.str());

            std::stringstream status;
            status << trackEditor.getStatus();
            statusText.setPosition(0.0f, window.getSize().y-2*statusText.getLocalBounds().height);
            statusText.setString(status.str());

            accumulator -= TIME_STEP;
        } 

        window.clear(sf::Color::Black);
        window.setView(camera);
        world.DrawDebugData();
        window.setView(window.getDefaultView());
        window.draw(infoText);
        window.draw(statusText);
        window.setView(camera);
        window.display();  

    }

    return 0;
}
