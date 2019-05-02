#ifndef KAESTLAB3_H
#define KAESTLAB3_H

#include <iostream>
#include <sys/time.h>
#include <fstream>
#include "exceptionStatus.h"
#include <vector>


struct connectNode{  int node1;  int node2; int cost; }; //holds network
struct netEdge{  int node; int path; struct connectNode* nextNode;}; //holds network
struct subNet{   int parent; int rank;   };

exception_status readInNetwork(std::string, std::vector<connectNode>&, int&); //read in network
std::vector<connectNode> sortByWeight(std::vector<connectNode> &toSort); //sorts the network list by weight
void findMST(struct connectNode result[], std::vector<connectNode> &network, int &size); //do the work
struct connectNode& organizeTree(struct connectNode mst[], int &size); //get it good for output


#endif
