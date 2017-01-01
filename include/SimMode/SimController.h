#ifndef SIMCONTROLLER_H
#define SIMCONTROLLER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>

#include "Controller/Keyboard.h"
#include "Controller/SFMLKeyboard.h"
#include "Renderer/SFMLRenderer.h"
#include "Entity/Listener/EntsColListener.h"
#include "SimMode/SimMode.h"

#include "Util/tsqueue.h"

#include <gtkmm.h>
#include <sstream>
#include <sigc++/sigc++.h>


class MainWindow;

class SimController : public SimMode::Observer
{
public:
    SimController(MainWindow* mw, SimMode* sim = nullptr);
    ~SimController();

    void setSim(SimMode* sim);

    void start();
    void stop();
    void resume();
    void pause();

    void showWindow();

    bool isRunning();
    bool isStarted();

    void setRTS(bool status);
    bool isRTS() const;

    void setTimeStep(const sf::Time& timeStep);
    void setTimeStep(float timeStep);
    sf::Time getTimeStep() const ;

    void update(SimMode::event_t et);

    Keyboard* getKeyController();

    // void notify();
    // TSQueue<unsigned int>& getMsgQueue();

private:
    SimMode* m_sim;
    MainWindow* m_mw;

    sf::RenderWindow m_window;
    bool m_window_visible;
    Camera m_camera;
    SFMLRenderer m_renderer;
    SFMLDebugDraw m_debugDraw;
    SFMLKeyboard m_keyboard;

    bool m_hasFocus;
    bool m_isRunning;
    bool m_isStarted;
    bool m_isRTS;

    sf::Clock m_updateClock;
    sf::Time m_timeStep;

    void handleEvents();
    void handleKeyPressed();
    void run();


    // // Dispatcher handler (multithreading)
    // Glib::Dispatcher m_Dispatcher;

    // // Thread-safe events queue
    // TSQueue<SimMode::event_t> m_msgq;

    // // Dispatcher handler.
    // void on_notification();
};

// inline void SimController::notify() 
// {
//     m_Dispatcher.emit();
// }

// inline TSQueue<unsigned int>& SimController::getMsgQueue()
// {
//     return m_msgq;
// }


#endif