
#include "SimMode/SimMode.h"
#include "SimMode/LearnMode.h"
#include "SimMode/RaceMode.h"

#include "Drivers/HumanDriver.h"
#include "Renderer/SFMLRenderer.h"
#include "Renderer/NoRenderer.h"
#include "Renderer/Renderer.h"
#include "Entity/Types.h"
#include "Entity/Car.h"
#include "Entity/TrackLine.h"
#include "Entity/TrackLink.h"
#include "Entity/Cube.h"
#include "Entity/Checkpoint.h"
#include "Entity/Listener/EntsColListener.h"
#include "Drivers/ASpeedFactory.h"
#include "Entity/Track.h"
#include "Entity/Spec/TrackSpec.h"

#include "NEAT/neat.h"
#include "SFMLDebugDraw.h"
#include "deg2rad.h"

#include <Box2D/Box2D.h>
#include <ctime>


int main (int argc, char* argv[]) {

    //***********RANDOM SETUP***************//
    std::srand( (unsigned)std::time( NULL ) );

    // --------------------------------------------------------------------------------
    // Load NEAT parameters
    // --------------------------------------------------------------------------------    
    if (argc != 2) {
        std::cerr << "A NEAT parameters file (.ne file) is required to run the experiments!" << std::endl;
        return -1;
    }
    NEAT::load_neat_params(argv[1],true);

    // Create important objects
    b2World world(b2Vec2(0.0f, 0.0f));

    EntsColListener entsListener;
    world.SetContactListener(&entsListener);


    // --------------------------------------------------------------------------------
    // Bodies section
    // --------------------------------------------------------------------------------

    TrackSpec ts;
    ts.load("Config/track004.xml");
    
    Track track(ts, &world);

    CarSpec carSpec;
    // carSpec.pos = track.getStartPos(1)->getPosition();
    // carSpec.angle = track.getStartPos(1)->getAngle();
    carSpec.groupIndex = -1;
    carSpec.rayVision.n = 16; 
    carSpec.rayVision.length = 80;
    carSpec.rayVision.showRays = false;
    carSpec.rayVision.dynamicRays = false;
    carSpec.rayVision.maxRayAngle = 70;
    carSpec.rayVision.filter = EntType::ENT_TRACKLINK | EntType::ENT_CUBE;
    carSpec.frontLeftTire.maxForwardSpeed = 250;
    carSpec.frontLeftTire.maxBackwardSpeed = -40;
    carSpec.frontLeftTire.maxDriveForce = 500;
    carSpec.frontLeftTire.maxLateralImpulse = 7.5;
    carSpec.frontRightTire = carSpec.frontLeftTire;
    carSpec.backLeftTire.maxForwardSpeed = 250;
    carSpec.backLeftTire.maxBackwardSpeed = -40;
    carSpec.backLeftTire.maxDriveForce = 300;
    carSpec.backLeftTire.maxLateralImpulse = 8.5;
    carSpec.backRightTire = carSpec.backLeftTire;   

    ASpeedFactory driverFactory(carSpec, ts.getStartPos(1)->pos, ts.getStartPos(1)->angle);

    // Read inital genome
    std::ifstream genomeSource("Config/autodriver001", std::ios::in); 
    char curword[20];
    int id;
    genomeSource >> curword;
    genomeSource >> id;
    NEAT::Genome* initGenome = new NEAT::Genome(id, genomeSource);
    genomeSource.close();

    // Create window for renderer
    sf::RenderWindow window(sf::VideoMode(1366, 768), "AutoSpeed Learning Simulator", 
        sf::Style::Default);
    window.setPosition(sf::Vector2i(10, 10));

    SFMLRenderer renderer(&window, &world);

    // Create my own car
    carSpec.rayVision.showRays = true;
    carSpec.rayVision.dynamicRays = true;

    Car car(carSpec, &world);
    car.setActive(true);
    car.setTransform(ts.getStartPos(1)->pos, ts.getStartPos(1)->angle - 90.0f * DEGTORAD);

    HumanDriver hd(&car, true);
    hd.left = sf::Keyboard::A;
    hd.right = sf::Keyboard::D;
    hd.accelerate = sf::Keyboard::W;
    hd.reverse = sf::Keyboard::S;

    LearnMode learnSim(&world, &renderer, &driverFactory, initGenome);
    learnSim.setExpTime(30.0);
    learnSim.setExtraDriver(&hd);

    RaceMode raceSim(&world, &renderer);
    raceSim.addDriver(&hd);

    SimMode* sim = &raceSim;
    sim->setConfig(SimMode::EXIT_ON_CLOSED);
    sim->setTimeStep(sf::seconds(0.01f));
    sim->setRTS(true);
    sim->start();

    // Clearning time!
    delete initGenome;
    
    /*
    for(std::vector<Checkpoint*>::iterator chpoint = chpoints.begin(); chpoint != chpoints.end(); ++chpoint)
        delete *chpoint;
    chpoints.clear();
    */

    return 0;
}
