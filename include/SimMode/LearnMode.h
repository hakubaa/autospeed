#ifndef LEARNMODE_H
#define LEARNMODE_H

#include "SimMode/SimMode.h"

#include "SimMode/LearnLog.h"
#include "Drivers/Driver.h"
#include "Drivers/DriverFactory.h"
#include "Entity/Spec/TrackSpec.h"
#include "Entity/Track.h"

#include "NEAT/neat.h"
#include "NEAT/network.h"
#include "NEAT/population.h"
#include "NEAT/organism.h"
#include "NEAT/genome.h"
#include "NEAT/species.h"

#include <Box2D/Box2D.h>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>


#include <stdexcept>
#include <queue>
#include <string>
#include <fstream>

class LearnMode : public SimMode {

protected:
    void initSim();

private:

    sf::Time m_expTime;
    sf::Time m_expTimer;

    int m_generation;
    NEAT::Population* m_pop;
    std::vector<Driver*> m_drivers;
    Track* m_track;
    
    // For changing track during simulation
    bool m_newtrack;
    TrackSpec m_newtrack_spec;
    

    DriverFactory* m_dfactory;
    Driver* m_driver;
    bool m_start_newgenr;

    void createDrivers();
    void clearDrivers();

public:
    LearnLog learnLog;

public:

    class Event : public SimMode::Event
    {
    public:
        CREATE_EVENT(new_msg);
        CREATE_EVENT(new_generation);
    };

    LearnMode(std::string genomefile, DriverFactory* df, const sf::Time& expTime);
    ~LearnMode();

    void update(const sf::Time& timeStep);

    const sf::Time& getExpTime() const;
    void setExpTime(const sf::Time& expTime);
    void setExpTime(float expTime);

    int getLastGener() const;

    void setExtraDriver(Driver* driver);
    void startNewGenr();
    void setTrack(const TrackSpec& tspec);

    void setDriverFactory(DriverFactory* dfactory);

    std::queue<std::string>* getPopMsgQueue();
};

inline std::queue<std::string>* LearnMode::getPopMsgQueue()
{
    if (m_pop != nullptr)
        return &m_pop->msg;
    else
        return nullptr;
}

inline void LearnMode::setDriverFactory(DriverFactory* dfactory)
{
    m_dfactory = dfactory;
}

#endif