#ifndef KAESTLAB3_H
#define KAESTLAB3_H

#include <iostream>
#include <sys/time.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "exceptionStatus.h"


struct connectNode{  //holds network
  int node1;
  int node2;
  int cost;
  connectNode(): node1(0), node2(0), cost(0)
  { }
  connectNode(int n1, int n2, int c): node1(n1), node2(n2), cost(c)
  { }
};
struct subNet{   int parent = 0; int rank = 0;   };

inline bool compareNode(const connectNode& a, const connectNode& b)
{return a.cost < b.cost;}

exception_status readInNetwork(std::string, std::vector<connectNode>&, int&); //read in network
void findMST(struct connectNode result[], std::vector<connectNode> &network, int &size); //do the work


#endif
