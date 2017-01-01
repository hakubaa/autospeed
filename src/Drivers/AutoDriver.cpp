#include "Drivers/AutoDriver.h"


AutoDriver::AutoDriver(std::ifstream& genomeFile, Car* car, bool randomize) {

    // Read genome from the file
    char curword[20];
    int id;
    genomeFile >> curword;
    genomeFile >> id;
    NEAT::Genome* genome = new NEAT::Genome(id, genomeFile);

    // Randomize weights - helpful when learning from the very beginning
    if (randomize) 
        genome->mutate_link_weights(1.0, 1.0, NEAT::COLDGAUSSIAN);
    genome->randomize_traits();

    // Create organsim on the base of read genome
    organism_ = new NEAT::Organism(0.0, genome, 1);
    organismOwner_ = true;
    car_ = car;

    initialize();
}

AutoDriver::AutoDriver(NEAT::Genome* genome, Car* car, int newId) {
    
    // Make copy of given genome and create organism
    NEAT::Genome* new_genome;
    if (newId == -1)
        newId = genome->genome_id;
    new_genome = genome->duplicate(newId); 
    organism_ = new NEAT::Organism(0.0, new_genome, 1);
    organismOwner_ = true;
    car_ = car;

    initialize();
}

AutoDriver::AutoDriver(NEAT::Organism* org, Car* car) {
    organism_ = org;
    car_ = car;
    organismOwner_ = false;

    initialize();
}

AutoDriver::~AutoDriver() {
    // destory organsim only when you are owner
    if (organismOwner_)
        delete organism_;
    if (car_ != nullptr)
        delete car_;
}

void AutoDriver::initialize() {
    actThreshold_ = 0.5;
}

int AutoDriver::update() {

    // Update sensors
    car_->rayVision->update();
            
    // vector of keeping input for NN
    double in[car_->rayVision->size()+3]; // add vertical & horizontal velocity

    in[0] = 1; // Bias
    in[1] = car_->getLinearVelocity().x;
    in[2] = car_->getLinearVelocity().y;

    for(int i = 0; i < car_->rayVision->size(); i++) 
        in[3+i] = car_->rayVision->output[i];

    // activate network and analyse outputs
    NEAT::Network* net = organism_->net;

    // verify whether no of inputs in NN is equal to vector with inputs
    assert(net->inputs.size() == car_->rayVision->size() + 3);

    // verify whether no of ouputs is equal to 4
    assert(net->outputs.size() == 4);

    net->load_sensors(in);
    if (!(net->activate())) return 0;

    //delete[] in;

    // There are four outputs: GO LEFT, GO RIGHT, GO UP, GO DOWN
    double outputs[4];
    for(int i = 0; i < net->outputs.size(); i++)
        outputs[i] = net->outputs[i]->activation;

    int controlState = 0;

    if (outputs[0] > actThreshold_)
        controlState |= CarTire::TDC_UP;
    if (outputs[1] > actThreshold_)
        controlState |= CarTire::TDC_RIGHT;
    if (outputs[2] > actThreshold_)
        controlState |= CarTire::TDC_LEFT;
    if (outputs[3] > actThreshold_)
        controlState |= CarTire::TDC_DOWN; 

    // Control car 
    car_->update(controlState);

    return controlState;
}