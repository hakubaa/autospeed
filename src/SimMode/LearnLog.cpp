#include "SimMode/LearnLog.h"

LearnLog::~LearnLog() {
    for(int i = 0; i < entries.size(); i++) {
        delete entries[i]->genome;
        delete entries[i];
    }
    entries.clear();
    mSpecies.clear();
    mGeners.clear();
}

void LearnLog::add(NEAT::Population* pop, int generation) {

    for(std::vector<NEAT::Species*>::iterator species = pop->species.begin(); 
        species != pop->species.end(); ++species) {

        int speciesId = (*species)->id;
        speciesIds.insert(speciesId);

        for(std::vector<NEAT::Organism*>::iterator org = (*species)->organisms.begin();
            org != (*species)->organisms.end(); ++org) {

            double fitness = (*org)->fitness;
            int gnome_id = (*org)->gnome->genome_id;
            NEAT::Genome* genome = (*org)->gnome->duplicate(gnome_id);

            Entry* entry = new Entry;
            entry->fitness = fitness;
            entry->generation = generation;
            entry->speciesId = speciesId;
            entry->genomeId = gnome_id;
            entry->genome = genome;
        
            entries.push_back(entry);
            mSpecies[speciesId].push_back(entry);
            mGeners[generation].push_back(entry);
            genersIds.insert(generation);
        }
    }
}   


std::set<int> LearnLog::getSpeciesIds() {
    return speciesIds;
}


std::set<int> LearnLog::getGenersIds() {
    return genersIds;
}


std::vector<LearnLog::Entry*> LearnLog::getSpecies(int id) {
    std::map<int, std::vector<Entry*> >::iterator result = mSpecies.find(id);
    if (result == mSpecies.end())
        return std::vector<Entry*>();
    return (*result).second;
}


std::vector<LearnLog::Entry*> LearnLog::getGener(int id) {
    std::map<int, std::vector<Entry*> >::iterator result = mGeners.find(id);
    if (result == mGeners.end())
        return std::vector<Entry*>();
    return (*result).second;
}


LearnLog::Entry* LearnLog::getSpeciesChamp(int id) {
    std::vector<LearnLog::Entry*> species = getSpecies(id);
    if (species.empty())
        return nullptr;
    else {
        Entry* champ = species[0];
        for(int i = 1; i < species.size(); i++) 
            if (champ->fitness < species[i]->fitness)
                champ = species[i];
        return champ;
    }
}

LearnLog::Entry* LearnLog::getGenerChamp(int id) {
    std::vector<LearnLog::Entry*> gener = getGener(id);
    if (gener.empty())
        return nullptr;
    else {
        Entry* champ = gener[0];
        for(int i = 1; i < gener.size(); i++) 
            if (champ->fitness < gener[i]->fitness)
                champ = gener[i];
        return champ;
    }
}