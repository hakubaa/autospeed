#include <iostream>
#include <fstream>
#include "NEAT/genome.h"
#include "NEAT/organism.h"
#include "NEAT/network.h"
#include "NEAT/nnode.h"
using namespace std;
using namespace NEAT;


int main() {

    Genome* start_genome;
    
    // Load initial genome from a file
    ifstream iFile("xorstartgenes",ios::in);

    char curword[20];
    iFile >> curword;

    int id;
    iFile >> id;

    cout << "Reading genome specification from the file ... " << endl;

    start_genome = new Genome(id,iFile);

    cout << "Genome created." << endl;

    iFile.close();


    // spwan genome

    //start_genome->mutate_link_weights(1.0, 1.0, COLDGAUSSIAN);
    //start_genome->randomize_traits();
    Organism* organism = new Organism(0.0, start_genome, 1);


    cout << "Nodes:" << endl;
    for(vector<NNode*>::iterator node = start_genome->nodes.begin(); node != start_genome->nodes.end(); ++node) {
        cout << "Node (id:" << (*node)->node_id << ", type:" << (*node)->type << ", node_label: " <<
            (*node)->gen_node_label << ")" << endl;
        for(vector<Link*>::iterator link = (*node)->incoming.begin(); link != (*node)->incoming.end(); ++link) 
            cout << "InLink (" << (*link)->trait_id << ")" << endl;
        for(vector<Link*>::iterator link = (*node)->outgoing.begin(); link != (*node)->outgoing.end(); ++link) 
            cout << "OutLink (" << (*link)->trait_id << ")" << endl;
    }

    cout << "Genes:" << endl;
    for(vector<Gene*>::iterator gene = start_genome->genes.begin(); gene != start_genome->genes.end(); ++gene) {

        cout << "Link from node " << (*gene)->lnk->in_node->node_id << " to node "
            << (*gene)->lnk->out_node->node_id << "; weight: " << (*gene)->lnk->weight << endl;
    }

    // evaluate organism (or rather it's network)

    Network* net = organism->net;

    // training sample for XOR
    double in[4][3]={{1.0, 0.0, 0.0},
                     {1.0, 0.0, 1.0},
                     {1.0, 1.0, 0.0},
                     {1.0, 1.0, 1.0}};
    double out[4]; //The four outputs
    bool success;

    // Check sensor and their activation value

    // cout << endl;
    // cout << "Sensor's activation test" << endl;
    // for(vector<NNode*>::iterator node = net->all_nodes.begin(); node != net->all_nodes.end(); ++node) 
    //     if ((*node)->type == 1) { // SESOR
    //         cout << "Sensor(" << (*node)->node_id << "):" << endl << "\tactivesum: " << (*node)->activesum << endl
    //             << "\tactivation: " << (*node)->activation << endl << "\tactive_flag: " << 
    //             (*node)->active_flag << endl;
    //     }

    // cout << "Net max depth: " << net->max_depth() << endl;

    net->load_sensors(in[3]);

    for(int i = 0; i < 10; i++) {
        net->activateKuba();
        for(vector<NNode*>::iterator node = net->outputs.begin(); node != net->outputs.end(); ++node)
            cout << "Output(" << (*node)->node_id << "): " << (*node)->activation << endl;
    }


    net->flush();
    cout << endl << "Activation origin" << endl;
    cout << endl << "max-depth: " << net->max_depth() << endl;
    net->load_sensors(in[3]);

    for(int i = 0; i <= net->max_depth(); i++) {
        net->activate();

        for(vector<NNode*>::iterator node = net->outputs.begin(); node != net->outputs.end(); ++node)
            cout << "Output(" << (*node)->node_id << "): " << (*node)->activation << endl;
    }

    // for(int count=0;count<=3;count++) {

    //     // set sensors' activation values at given value (there are three input nodes as well as three input values)
    //     net->load_sensors(in[count]);

    //     //Relax net and get output
    //     success = net->activate();

    //     //Find the maximum number of neurons between an ouput and an input
    //     int net_depth = net->max_depth();

    //     cout << "net_depth: " << net_depth << endl;

    //     //use depth to ensure relaxation 
    //     for (int relax = 0; relax <= net_depth; relax++) {
    //         success=net->activate();
    //         double this_out=(*(net->outputs.begin()))->activation;
    //     }

    //     out[count] = (*(net->outputs.begin()))->activation;

    //     net->flush();

    // }

    // double errorsum;
    // if (success) {
    //     errorsum = (fabs(out[0])+fabs(1.0-out[1])+fabs(1.0-out[2])+fabs(out[3]));
    //     organism->fitness = pow((4.0-errorsum),2);
    //     organism->error = errorsum;
    // } else {
    //     //The network is flawed (shouldnt happen)
    //     errorsum = 999.0;
    //     organism->fitness = 0.001;
    // }

    // for(int i = 0; i < 4; i++) {
    //     cout << "[ ";
    //     for (int j = 0; j < sizeof(in[j])/sizeof(*in[j]); j++)
    //         cout << in[i][j] << " ";
    //     cout << "] -> " << out[i] << endl;
    // }
    // cout << "Errorsum: " << errorsum << "; fitness: " << organism->fitness << endl;

    //Keep a record of the innovation and node number we are on
    // cur_node_id=new_genome->get_last_node_id();
    // cur_innov_num=new_genome->get_last_gene_innovnum();

    delete organism;

    return 0;
}