#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Entry {
    double fitness;
    int generation;
    int speciesId;
    int genomeId;
};


int main() {
    map<int, vector<Entry*> > species;

    Entry entry;
    entry.fitness = 14.02;
    entry.generation = 0;
    entry.speciesId = 0;
    entry.genomeId = 10;
    species[0].push_back(&entry);

    Entry entry2;
    entry2.fitness = 14.09;
    entry2.generation = 0;
    entry.speciesId = 0;
    entry.genomeId = 10;
    species[0].push_back(&entry2);

    species[1].push_back(&entry);

    for(map<int, vector<Entry*> >::iterator ii = species.begin(); ii != species.end(); ++ii) {
        std::vector<Entry*> ent = (*ii).second;
        cout << "Species " << (*ii).first << std::endl;
        for(int i = 0; i < ent.size(); i++) 
            cout << ent[i]->fitness << std::endl;
    }

    return 0;
}