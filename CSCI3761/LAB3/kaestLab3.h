#ifndef KAESTLAB3_H
#define KAESTLAB3_H

#include <iostream>
#include <sys/time.h>
#include <fstream>
#include "exceptionStatus.h"
#include <vector>


struct connectNode{  int node1;  int node2; int cost; }; //holds network
struct subNet{   int parent = 0; int rank = 0;   };

exception_status readInNetwork(std::string, std::vector<connectNode>&, int&); //read in network
std::vector<connectNode> sortByWeight(std::vector<connectNode> &toSort); //sorts the network list by weight
void findMST(struct connectNode result[], std::vector<connectNode> &network, int &size); //do the work


#endif
