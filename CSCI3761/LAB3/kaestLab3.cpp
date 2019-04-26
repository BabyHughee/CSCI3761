#include "kaestLab3.h"


/**Read in the network data line by line into an array
   *\param file is the file we are reading in from
   *\param input is the vector to put the network into
   *\param numberNodes is the amount of nodes in the network
   *\return error tracks if there was an error, what type, and where in the
                                                                          file.*/
exception_status readInNetwork(std::string file, std::vector<connectNode> &input, int numberNodes){
  exception_status error;

    std::ifstream infile;

        infile.open(file);

        ///////////check file/////////
      if (!infile.is_open() || infile.fail()) {
          // set error
          error.badCall("file_invalid");
          return error; // if the file didn't read, no need to continue.
      }

    infile >> numberNodes;//find initial node size
    infile >> std::ws; //strip initial whitespace

    int count = 0;

    while(!infile.eof()){

      count++;

      connectNode tempContainer;
      std::string temp;

      //---------node1--------
      std::getline(infile, temp, ' '); //read the current word up to space

      tempContainer.node1 = std::atoi(temp.c_str());

      //---------node2--------
      std::getline(infile, temp, ' '); //read the current word up to space

      tempContainer.node2 = std::atoi(temp.c_str());

      //---------cost--------
      std::getline(infile, temp, '\n'); //read the current word up to endline

      tempContainer.cost = std::atoi(temp.c_str());

      input.emplace_back(tempContainer);

      infile >> std::ws;

    if (infile.fail()) {
        // set error
        error.badCall("input_error_line_");
        error.which = count;
        return error; // if the file didn't read correctly, no need to continue.
    }
  }

  return error;
}
