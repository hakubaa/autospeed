/*
 Copyright 2001 The University of Texas at Austin

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "NEAT/pole1.h"
#include <cstring>

//#define NO_SCREEN_OUT 
   
//Perform evolution on single pole balacing, for gens generations
Population *pole1_test(int gens) {
    Population *pop=0;
    Genome *start_genome;
    char curword[20];
    int id;

    ostringstream *fnamebuf;
    int gen;

    int expcount;
    int status;
    int runs[NEAT::num_runs];
    int totalevals;
    int samples;  //For averaging

    memset (runs, 0, NEAT::num_runs * sizeof(int));

    ifstream iFile("pole1startgenes",ios::in);

    cout<<"START SINGLE POLE BALANCING EVOLUTION"<<endl;

    cout<<"Reading in the start genome"<<endl;
    //Read in the start Genome
    iFile>>curword;
    iFile>>id;
    cout<<"Reading in Genome id "<<id<<endl;
    start_genome=new Genome(id,iFile);
    iFile.close();

    //Run multiple experiments
    for(expcount=0;expcount<NEAT::num_runs;expcount++) {

        cout<<"EXPERIMENT #"<<expcount<<endl;

        cout<<"Start Genome: "<<start_genome<<endl;

        //Spawn the Population
        cout<<"Spawning Population off Genome"<<endl;

        pop=new Population(start_genome,NEAT::pop_size);

        cout<<"Verifying Spawned Pop"<<endl;
        pop->verify();

        for (gen=1;gen<=gens;gen++) {
            cout<<"Generation "<<gen<<endl;

            fnamebuf=new ostringstream();
            (*fnamebuf)<<"gen_"<<gen<<ends;  //needs end marker

            #ifndef NO_SCREEN_OUT
            cout<<"name of fname: "<<fnamebuf->str()<<endl;
            #endif  

            char temp[50];
            sprintf (temp, "gen_%d", gen);

            status=pole1_epoch(pop,gen,temp);
            //status=(pole1_epoch(pop,gen,fnamebuf->str()));

            if (status) {
                runs[expcount]=status;
                gen=gens+1; // sth like break the loop
            }

            fnamebuf->clear();
            delete fnamebuf;

        }

        if (expcount<NEAT::num_runs-1) delete pop;
    }

    totalevals=0;
    samples=0;
    for(expcount=0;expcount<NEAT::num_runs;expcount++) {
        cout<<runs[expcount]<<endl;
        if (runs[expcount]>0)
        {
            totalevals+=runs[expcount];
            samples++;
        }
    }

    cout<<"Failures: "<<(NEAT::num_runs-samples)<<" out of "<<NEAT::num_runs<<" runs"<<endl;
    cout<<"Average evals: "<<(samples>0 ? (double)totalevals/samples : 0)<<endl;

    return pop;

}

int pole1_epoch(Population *pop,int generation,char *filename) {
    vector<Organism*>::iterator curorg;
    vector<Species*>::iterator curspecies;
    //char cfilename[100];
    //strncpy( cfilename, filename.c_str(), 100 );

    //ofstream cfilename(filename.c_str());

    bool win=false;
    int winnernum;

    //Evaluate each organism on a test
    for(curorg=(pop->organisms).begin();curorg!=(pop->organisms).end();++curorg) {
        if (pole1_evaluate(*curorg)) win=true;
    }

    //Average and max their fitnesses for dumping to file and snapshot
    for(curspecies=(pop->species).begin();curspecies!=(pop->species).end();++curspecies) {

        //This experiment control routine issues commands to collect ave
        //and max fitness, as opposed to having the snapshot do it, 
        //because this allows flexibility in terms of what time
        //to observe fitnesses at

        (*curspecies)->compute_average_fitness();
        (*curspecies)->compute_max_fitness();
    }

    //Take a snapshot of the population, so that it can be
    //visualized later on
    //if ((generation%1)==0)
    //  pop->snapshot();

    //Only print to file every print_every generations
    if  (win || ((generation%(NEAT::print_every))==0))
        pop->print_to_file_by_species(filename);

    if (win) {
        for(curorg=(pop->organisms).begin();curorg!=(pop->organisms).end();++curorg) {
            if ((*curorg)->winner) {
                winnernum=((*curorg)->gnome)->genome_id;
                cout<<"WINNER IS #"<<((*curorg)->gnome)->genome_id<<endl;
            }
        }    
    }

    //Create the next generation
    pop->epoch(generation);

    if (win) return ((generation-1)*NEAT::pop_size+winnernum);
    else return 0;

}

bool pole1_evaluate(Organism *org) {
    Network *net;

    int numnodes;  /* Used to figure out how many nodes
            should be visited during activation */
    int thresh;  /* How many visits will be allowed before giving up 
          (for loop detection) */

    //  int MAX_STEPS=120000;
    int MAX_STEPS=100000;

    net=org->net;
    numnodes=((org->gnome)->nodes).size();
    thresh=numnodes*2;  //Max number of visits allowed per activation

    //Try to balance a pole now
    org->fitness = go_cart(net,MAX_STEPS,thresh);

    #ifndef NO_SCREEN_OUT
    cout<<"Org "<<(org->gnome)->genome_id<<" fitness: "<<org->fitness<<endl;
    #endif

    //Decide if its a winner
    if (org->fitness>=MAX_STEPS) { 
        org->winner=true;
        return true;
    } else {
        org->winner=false;
        return false;
    }

}

//     cart_and_pole() was take directly from the pole simulator written
//     by Richard Sutton and Charles Anderson.
int go_cart(Network *net,int max_steps,int thresh)
{
    float x,         /* cart position, meters */
         x_dot,         /* cart velocity */
         theta,         /* pole angle, radians */
         theta_dot;     /* pole angular velocity */
    int steps=0,y;

    int random_start=1;

    double in[5];  //Input loading array

    double out1;
    double out2;

    //     double one_degree= 0.0174532;    /* 2pi/360 */
    //     double six_degrees=0.1047192;
    double twelve_degrees=0.2094384;
    //     double thirty_six_degrees= 0.628329;
    //     double fifty_degrees=0.87266;

    vector<NNode*>::iterator out_iter;

    if (random_start) {
        /*set up random start state*/
        x = (lrand48()%4800)/1000.0 - 2.4;
        x_dot = (lrand48()%2000)/1000.0 - 1;
        theta = (lrand48()%400)/1000.0 - .2;
        theta_dot = (lrand48()%3000)/1000.0 - 1.5;
    } else 
        x = x_dot = theta = theta_dot = 0.0;

    /*--- Iterate through the action-learn loop. ---*/
    while (steps++ < max_steps) {

        /*-- setup the input layer based on the four iputs --*/
        //setup_input(net,x,x_dot,theta,theta_dot);
        in[0]=1.0;  //Bias
        in[1]=(x + 2.4) / 4.8;;
        in[2]=(x_dot + .75) / 1.5;
        in[3]=(theta + twelve_degrees) / .41;
        in[4]=(theta_dot + 1.0) / 2.0;
        net->load_sensors(in);

        //activate_net(net);   /*-- activate the network based on the input --*/
        //Activate the net
        //If it loops, exit returning only fitness of 1 step
        if (!(net->activate())) return 1;

        /*-- decide which way to push via which output unit is greater --*/
        out_iter=net->outputs.begin();
        out1=(*out_iter)->activation;
        ++out_iter;
        out2=(*out_iter)->activation;
        if (out1 > out2)
            y = 0;
        else
            y = 1;

        /*--- Apply action to the simulated cart-pole ---*/
        cart_pole(y, &x, &x_dot, &theta, &theta_dot);

        /*--- Check for failure.  If so, return steps ---*/
        if (x < -2.4 || x > 2.4  || theta < -twelve_degrees ||
            theta > twelve_degrees) 
        return steps;             
    }

    return steps;
} 


//     cart_and_pole() was take directly from the pole simulator written
//     by Richard Sutton and Charles Anderson.
//     This simulator uses normalized, continous inputs instead of 
//    discretizing the input space.
/*----------------------------------------------------------------------
   cart_pole:  Takes an action (0 or 1) and the current values of the
 four state variables and updates their values by estimating the state
 TAU seconds later.
----------------------------------------------------------------------*/
void cart_pole(int action, float *x,float *x_dot, float *theta, float *theta_dot) {
    float xacc,thetaacc,force,costheta,sintheta,temp;

    const float GRAVITY=9.8;
    const float MASSCART=1.0;
    const float MASSPOLE=0.1;
    const float TOTAL_MASS=(MASSPOLE + MASSCART);
    const float LENGTH=0.5;     /* actually half the pole's length */
    const float POLEMASS_LENGTH=(MASSPOLE * LENGTH);
    const float FORCE_MAG=10.0;
    const float TAU=0.02;   /* seconds between state updates */
    const float FOURTHIRDS=1.3333333333333;

    force = (action>0)? FORCE_MAG : -FORCE_MAG;
    costheta = cos(*theta);
    sintheta = sin(*theta);

    temp = (force + POLEMASS_LENGTH * *theta_dot * *theta_dot * sintheta)
    / TOTAL_MASS;

    thetaacc = (GRAVITY * sintheta - costheta* temp)
    / (LENGTH * (FOURTHIRDS - MASSPOLE * costheta * costheta
         / TOTAL_MASS));

    xacc  = temp - POLEMASS_LENGTH * thetaacc* costheta / TOTAL_MASS;

    /*** Update the four state variables, using Euler's method. ***/

    *x  += TAU * *x_dot;
    *x_dot += TAU * xacc;
    *theta += TAU * *theta_dot;
    *theta_dot += TAU * thetaacc;
}
