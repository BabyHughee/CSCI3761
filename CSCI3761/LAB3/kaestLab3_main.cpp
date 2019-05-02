#include "kaestLab3.h"

#define MAX_LEN 1073741824;


int main(int argc, char* argv[]) {
//Declare the variables needed
std::vector<connectNode> network;
int networkSize = 0;
exception_status error;

// int count = 1;



if (argc != 2){
  std::cerr << "./MST [textfile]" << std::endl;
  exit(1);
}

  /*------------CLOCK STATUS------------*/
  /*-*/  struct timeval start, stop; /*-*/
  /*-*/  gettimeofday(&start, NULL); /*-*/
  /*------------CLOCK STATUS------------*/



//Prepare for finding the minimal spanning tree
  error = readInNetwork(argv[1], network, networkSize); //read in the network
  if(error.error == true){ std::cout << error.status << std::endl; } //output error
  connectNode foundMST[networkSize - 1];
  network = sortByWeight(network); //sort the nodes by weight

  findMST(foundMST, network, networkSize);


  /*--------------------------CLOCK STATUS-------------------------*/
  /*-*/    gettimeofday(&stop, NULL);                           /*-*/
  /*-*/    double elapsed = 0;                                  /*-*/
  /*-*/    elapsed = (stop.tv_sec - start.tv_sec) * 1000.0f +   /*-*/
  /*-*/              (stop.tv_usec - start.tv_usec) / 1000.0f;  /*-*/
  /*-*/    std::cout << "Total Execution time = " << elapsed    /*-*/
  /*-*/              << " ms" << std::endl;                     /*-*/
  /*--------------------------CLOCK STATUS-------------------------*/

int cost = 0;
for (int i = 0; i < networkSize - 1; ++i){
    cost += foundMST[i].cost;
  }

  std::cout << "Minimum Cost = " << cost << std::endl;


  std::cout << "Minimum Spanning Tree (T) : " << std::endl;

int j = 0;
  for (int i = 1; i < networkSize - 1; ++i){

      if (j == 8){
        std::cout << '\n';
        j = 0;
      }

      std::cout << "(" << foundMST[i].node1 << "," << foundMST[i].node2 << ")";
      j++;

      if(i != (networkSize - 2)){
        std::cout << ", ";
      }


    }

    std::cout << std::endl;


  return 0;
}




// for (int i = 0; i < network.size(); i++){
//   std::cout << network[i].node1 << " ";
//   std::cout << network[i].node2 << " ";
//   std::cout << network[i].cost << " ";
//   std::cout << std::endl;
// }


// for (int i = 0; i < network.size(); i++){
//   std::cout << network[i].node1 << " ";
//   std::cout << network[i].node2 << " ";
//   std::cout << network[i].cost << " ";
//   std::cout << std::endl;
// }

  // std::cout << std::endl;
  // std::cout << std::endl;
  // std::cout << std::endl;



    // 66 - 77
// for (int i = 0; i < networkSize - 1; ++i){
// std::cout <<  foundMST[i].node1 << " - " << foundMST[i].node2 << std::endl;
//   }



// 66 - 77
// for (int i = 1; i < networkSize - 1; ++i){
//     weight += foundMST[i].cost;
//     std::cout << ",";
//     if (count == 8){
//       std::cout << i;
//       std::cout << std::endl;
//       count = 0;
//
//     }
//     std::cout << "(" << foundMST[i].node1 << "," << foundMST[i].node2 << ")";
//
//     count++;
//   }
  //
  // std::cout << std::endl;
  // std::cout << weight;
  // std::cout << std::endl;
  // std::cout << std::endl;
