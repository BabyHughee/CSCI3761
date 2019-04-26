#include "kaestLab3.h"

#define MAX_LEN 1073741824;



int main(int argc, char* argv[]) {

  if (argc != 2){
    std::cerr << "./MST [textfile]" << std::endl;
    exit(1);
  }



  std::cout << argv[1] << std::endl;


  readIn();









  return 0;
}
