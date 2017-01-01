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
#ifndef POLE1_H
#define POLE1_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include "NEAT/neat.h"
#include "NEAT/network.h"
#include "NEAT/population.h"
#include "NEAT/organism.h"
#include "NEAT/genome.h"
#include "NEAT/species.h"

using namespace std;

using namespace NEAT;

//Single pole balancing evolution routines ***************************
Population *pole1_test(int gens); 
bool pole1_evaluate(Organism *org);
int pole1_epoch(Population *pop,int generation,char *filename);
int go_cart(Network *net,int max_steps,int thresh); //Run input
//Move the cart and pole
void cart_pole(int action, float *x,float *x_dot, float *theta, float *theta_dot);

#endif