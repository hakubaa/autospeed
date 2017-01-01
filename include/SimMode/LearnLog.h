#ifndef LEARNLOG_H
#define LEARNLOG_H

#include "NEAT/neat.h"
#include "NEAT/network.h"
#include "NEAT/population.h"
#include "NEAT/organism.h"
#include "NEAT/genome.h"
#include "NEAT/species.h"

#include <vector>
#include <map>
#include <iostream>
#include <set>

/* LearnLog

    - keep track of all genoms
    - keep track of fitness for each generation within the population, species

*/

class LearnLog {

public:
    struct Entry {
        NEAT::Genome* genome;
        double fitness;
        int generation;
        int speciesId;
        int genomeId;
    };

private:
    std::vector<Entry*> entries;
    std::map<int, std::vector<Entry*> > mSpecies;
    std::map<int, std::vector<Entry*> > mGeners;

    std::set<int> speciesIds;
    std::set<int> genersIds;

public:
    LearnLog() { }
    ~LearnLog();

    void add(NEAT::Population* pop, int generation);  

    std::set<int> getSpeciesIds();
    std::set<int> getGenersIds();

    std::vector<Entry*> getSpecies(int id);
    std::vector<Entry*> getGener(int id);

    Entry* getSpeciesChamp(int id);
    Entry* getGenerChamp(int id);
};


#endif