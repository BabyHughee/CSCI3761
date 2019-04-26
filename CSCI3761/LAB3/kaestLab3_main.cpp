#include "kaestLab3.h"

#define MAX_LEN 1073741824;



int main(int argc, char* argv[]) {
  /*------------CLOCK STATUS------------*/
  /*-*/  struct timeval start, stop; /*-*/
  /*-*/  gettimeofday(&start, NULL); /*-*/
  /*------------CLOCK STATUS------------*/


  if (argc != 2){
    std::cerr << "./MST [textfile]" << std::endl;
    exit(1);
  }



  std::cout << argv[1] << std::endl;


  readIn();







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
