#ifndef KAESTLAB3_H
#define KAESTLAB3_H

#include <iostream>
#include <sys/time.h>
#include <fstream>
#include "exceptionStatus.h"
#include <vector>


struct connectNode{  int node1;  int node2; int cost; }; //holds network


exception_status readInNetwork(std::string, std::vector<connectNode>&, int); //read in network





#endif
