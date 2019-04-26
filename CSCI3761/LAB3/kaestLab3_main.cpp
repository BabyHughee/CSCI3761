#include "kaestLab3.h"

#define MAX_LEN 1073741824;


int main(int argc, char* argv[]) {
if (argc != 2){
  std::cerr << "./MST [textfile]" << std::endl;
  exit(1);
}

  /*------------CLOCK STATUS------------*/
  /*-*/  struct timeval start, stop; /*-*/
  /*-*/  gettimeofday(&start, NULL); /*-*/
  /*------------CLOCK STATUS------------*/

//Declare the variables needed
std::vector<connectNode> network;
int networkSize = 0;
exception_status error;

//Read in stuff
  error = readInNetwork(argv[1], network, networkSize); //read in the network
  if(error.error == true){ std::cout << error.status << std::endl; } //output error



for (int i = 0; i < network.size(); i++){
  std::cout << network[i].node1 << " ";
  std::cout << network[i].node2 << " ";
  std::cout << network[i].cost << " ";
  std::cout << std::endl;
}


  /*--------------------------CLOCK STATUS-------------------------*/
  /*-*/    gettimeofday(&stop, NULL);                           /*-*/
  /*-*/    double elapsed = 0;                                  /*-*/
  /*-*/    elapsed = (stop.tv_sec - start.tv_sec) * 1000.0f +   /*-*/
  /*-*/              (stop.tv_usec - start.tv_usec) / 1000.0f;  /*-*/
  /*-*/    std::cout << "Total Execution time = " << elapsed    /*-*/
  /*-*/              << " ms" << std::endl;                     /*-*/
  /*--------------------------CLOCK STATUS-------------------------*/
  return 0;
}
