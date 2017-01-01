#include "SimMode/SimController.h"
#include "GUI/MainWindow.h"

SimController::SimController(MainWindow* mw, SimMode* sim) :
    m_mw(mw),
    m_sim(sim),
    m_window(),
    m_camera(&m_window),
    m_hasFocus(false),
    m_renderer(&m_window, &m_camera),
    m_debugDraw(m_window),
    m_isStarted(false),
    m_isRunning(false),
    m_window_visible(false)
{
    std::cout << "SimController::SimController()" << std::endl;

    // draw default physics objects
    m_debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
    if (m_sim != nullptr)
    {
        m_sim->getb2World()->SetDebugDraw(&m_debugDraw);
        m_sim->addObserver(this);
    }

    // m_Dispatcher.connect(
    //     sigc::mem_fun(*this, &SimController::on_notification));
}

SimController::~SimController()
{
    std::cout << "SimController::~SimController() BEGIN" << std::endl;
    std::cout << "SimController::~SimController() END" << std::endl;
}

void SimController::setSim(SimMode* sim) 
{
    if (!m_isRunning)
    {
        m_sim = sim;
        m_sim->getb2World()->SetDebugDraw(&m_debugDraw);
        m_sim->addObserver(this);
    }
}

void SimController::run()
{
    std::cout << "SimController::run() BEGIN" << std::endl;

    sf::Time accumulator = sf::seconds(0.0f);

    while (m_isStarted) 
    {
        handleEvents();
        handleKeyPressed();

        if (m_isRunning)
        {
            if (m_isRTS) 
            {
                accumulator += m_updateClock.restart();
                while (accumulator > m_timeStep) 
                {
                    m_sim->update(m_timeStep);
                    accumulator -= m_timeStep;
                } 
            } 
            else 
            {
                m_sim->update(m_timeStep);
            }
        }

        if (m_window_visible)
        {
            m_camera.update();
            m_renderer.render(nullptr, m_sim);

            std::stringstream s;
            s << "AutoSpeed Learning Simulator (FPS: " << m_renderer.getFPS() << ")";
            m_window.setTitle(s.str());
        }
    }    

    std::cout << "SimController::run() END" << std::endl;
}

void SimController::handleEvents()
{
    if (m_window_visible) 
    {
        sf::Event event;
        while (m_window.pollEvent(event)) 
        {
             switch(event.type) 
             {
                case sf::Event::Closed:
                    // m_window.close();
                    m_window.setVisible(false);
                    m_window_visible = false;
                    m_hasFocus = false;
                    break;    

                case sf::Event::LostFocus:
                    m_hasFocus = false;
                    break;

                case sf::Event::GainedFocus:
                    m_hasFocus = true;
                    break;        

                case sf::Event::KeyPressed:
                    m_keyboard.setKeyState(event.key, true);
                    break;

                case sf::Event::KeyReleased:
                    m_keyboard.setKeyState(event.key, false);
                    break;

                default:
                    break;
            }
            m_camera.handleEvent(event, m_sim->getb2World());
        }
    }
}



void SimController::handleKeyPressed()
{
    if (m_window_visible && m_hasFocus)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            m_camera.rotate(0.5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
            m_camera.rotate(-0.5);
    }
}


void SimController::stop() 
{
    if (m_isStarted) 
    {
        m_isRunning = false;
        m_isStarted = false;
    }
}

void SimController::start() 
{
    if (!m_isStarted) 
    {
        m_isStarted = true;
        m_isRunning = true;

        m_sim->initSim();
        m_updateClock.restart();

        m_window.create(sf::VideoMode(1366, 768), "AutoSpeed Learning Simulator", 
            sf::Style::Default);
        m_window.setPosition(sf::Vector2i(50, 50));
        m_window_visible = true;
        m_hasFocus = true;

        run();
    }
    else
    {
        std::cout << "SimController: m_isStarted = True" << std::endl;
    }
}

void SimController::showWindow()
{
    if (!m_window_visible) 
    {
        m_window.setVisible(true);
        m_window_visible = true;
        m_hasFocus = true;
    }
}

void SimController::pause() {
    if (m_isStarted)
        m_isRunning = false;
}

void SimController::resume() {
    if (m_isStarted) {
        m_updateClock.restart();
        m_isRunning = true;
    }
}

bool SimController::isRunning() {
    return m_isRunning;
}

bool SimController::isStarted() {
    return m_isStarted;
}

sf::Time SimController::getTimeStep() const 
{ 
    return m_timeStep; 
}

void SimController::setTimeStep(const sf::Time& timeStep) 
{ 
    m_timeStep = timeStep; 
}

void SimController::setTimeStep(float timeStep) 
{ 
    m_timeStep = sf::seconds(timeStep); 
}

void SimController::setRTS(bool rts) 
{ 
    m_isRTS = rts; 
}

bool SimController::isRTS() const
{ 
    return m_isRTS; 
}

void SimController::update(SimMode::event_t simEvent)
{
    m_mw->getEventsQueue().push(simEvent);
    m_mw->notify();  
}

// void SimController::on_notification()
// {
//    while (!m_msgq.empty())
//     {
//         int event = m_msgq.front();
//         m_msgq.pop();

//         if (event == MainWindow::Msg::show_window())
//         {
//             showWindow();
//         }
//     }    
// }

Keyboard* SimController::getKeyController()
{
    return &m_keyboard;
}