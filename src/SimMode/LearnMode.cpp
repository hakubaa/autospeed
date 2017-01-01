#include "SimMode/LearnMode.h"

/*-------------------------------------------------------
    Constructors & so on
--------------------------------------------------------- */

LearnMode::LearnMode(std::string genomefile, DriverFactory* df, const sf::Time& expTime) :
    SimMode(),
    m_expTime(expTime),
    m_dfactory(df), 
    m_expTimer(sf::seconds(0.0)),
    m_driver(nullptr),
    m_generation(0),
    m_pop(nullptr),
    m_start_newgenr(false),
    m_track(nullptr),
    m_newtrack(false)
{
    std::ifstream genomeSource(genomefile.c_str(), std::ios::in); 
    if (genomeSource.is_open())
    {
        char curword[20];
        int id;
        genomeSource >> curword;
        genomeSource >> id;
        NEAT::Genome genome(id, genomeSource);
        genomeSource.close();

        // Init population
        m_pop = new NEAT::Population(&genome, NEAT::pop_size);
    } 
    else
    {
        throw std::runtime_error("LearMode::LearnMode() - unable to open file with genome");
    }
}

LearnMode::~LearnMode() 
{
    std::cout << "LearnMode::~LearnMode() BEGIN" << std::endl;
    clearDrivers();
    std::cout << " ... drivers DONE" << std::endl;
    if (m_pop != nullptr)
        delete m_pop;
    if (m_track != nullptr)
        delete m_track;
    std::cout << "LearnMode::~LearnMode() END" << std::endl;
}

/*-------------------------------------------------------
    Logic
--------------------------------------------------------- */

void LearnMode::update(const sf::Time& timeStep) 
{
    m_expTimer += timeStep;

    // Evaluate all drivers
    for(std::vector<Driver*>::iterator driver = m_drivers.begin(); driver != m_drivers.end(); ++driver) 
    {
        if ((*driver)->isActive()) 
            (*driver)->update();
    }     

    if (m_driver != nullptr) 
    {
        if (m_driver->isActive())
            m_driver->update();
    }

    // Start new generation with space
    // if (m_renderer != nullptr)
    // {
    //     if (m_renderer->hasFocus())
    //     {
    //         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
    //         {
    //             while(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
    //             m_start_newgenr = true;
    //         }
    //     }
    // }

    SimMode::update(timeStep);

    if (m_expTimer > m_expTime)
        m_start_newgenr = true;

    // time for new generation
    if (m_start_newgenr) 
    {        
        std::cout << "LearnMode::update - new generation" << std::endl;
        // update fitness
        for(std::vector<Driver*>::iterator driver = m_drivers.begin(); driver != m_drivers.end(); ++driver) 
            (*driver)->updateFitness();

        // make some log
        //learnLog.add(m_pop, m_generation);

        //Create next generation
        m_pop->epoch(++m_generation);

        // notify observers about sth very important        
        notify(LearnMode::Event::new_generation());

        initSim();
    }

}

void LearnMode::initSim()
{
    if (m_newtrack)
    {
        delete m_track;
        m_track = new Track(m_newtrack_spec, &m_world);
        m_newtrack = false;
    }

    clearDrivers();
    createDrivers();
    m_expTimer = sf::seconds(0.0f);
    m_start_newgenr = false;   
}

/*-------------------------------------------------------
    Mange drivers
---------------------------------------------------------*/

void LearnMode::createDrivers() {
    if (m_pop != nullptr)
    {
        for(std::vector<NEAT::Organism*>::iterator organism = m_pop->organisms.begin(); 
            organism != m_pop->organisms.end(); ++organism) 
        {
            Driver* driver = m_dfactory->create(*organism, &m_world);
            driver->setActive(true);
            m_drivers.push_back(driver);

        }   
    }
}

void LearnMode::clearDrivers() 
{
    for (unsigned int i = 0; i < m_drivers.size(); i++)
        delete m_drivers[i];
    m_drivers.clear();  
}


/*-------------------------------------------------------
    Controling methods
--------------------------------------------------------- */

const sf::Time& LearnMode::getExpTime() const 
{ 
    return m_expTime; 
}

void LearnMode::setExpTime(const sf::Time& expTime) 
{ 
    m_expTime = expTime; 
}

void LearnMode::setExpTime(float expTime) 
{ 
    m_expTime = sf::seconds(expTime); 
}

int LearnMode::getLastGener() const 
{ 
    return m_generation; 
}

void LearnMode::setExtraDriver(Driver* driver) 
{ 
    m_driver = driver;
}

void LearnMode::startNewGenr()
{
    m_start_newgenr = true;
}

void LearnMode::setTrack(const TrackSpec& tspec)
{
    if (m_track != nullptr)
    {
        m_newtrack = true;
        m_newtrack_spec = tspec;
    }
    else
    {
        m_track = new Track(tspec, &m_world);
    }
}