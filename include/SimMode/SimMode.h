#ifndef SIMMODE_H
#define SIMMODE_H

#include <iostream>
#include <vector>

#include <Box2D/Box2D.h>
#include <SFML/System/Time.hpp>

#include "Entity/Listener/EntsColListener.h"


#define CREATE_EVENT(EVENT_NAME) \
    static __attribute__((always_inline)) event_t EVENT_NAME() { return __COUNTER__; }


class SimMode {

public:

    typedef unsigned int event_t;

    class Event
    {
    private:
        Event();
        Event(const Event&);
        Event& operator=(const Event&);
    };

    class Observer
    {
    public:
        virtual ~Observer() { }
        virtual void update(event_t et) = 0;
    };

    SimMode();
    virtual ~SimMode() { 
        std::cout << "SimMode::~SimMode() BEGIN" << std::endl;
        std::cout << "bodies no = " << m_world.GetBodyCount() << std::endl;
        std::cout << "joints no = " << m_world.GetJointCount() << std::endl;
        std::cout << "SimMode::~SimMode() END" << std::endl;
    }

    // virtual void start();
    // virtual void stop();
    // virtual void resume();
    // virtual void pause();
    // virtual void restart();

    void addObserver(SimMode::Observer* observer);
    
    virtual void update(const sf::Time& timeStep);
    virtual void initSim();

    b2World* getb2World();
protected:
    b2World m_world;
    EntsColListener m_entsListener;

    void notify(event_t et);

private:
    std::vector<Observer*> m_observers;
 
};

inline void SimMode::initSim() {}
// inline void SimMode::start() {}
// inline void SimMode::stop() {}
// inline void SimMode::resume() {}
// inline void SimMode::pause() {}
// inline void SimMode::restart() {}

inline b2World* SimMode::getb2World() 
{
    return &m_world;
}
#endif