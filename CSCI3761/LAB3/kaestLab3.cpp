#include "kaestLab3.h"

/**Function to find a set of i and parents
  *\param subset is our list of parents and rank
  *\param i is to be inserted correctly
  *\return return the parent of i */
int findCycle(struct subNet subsets[], int& i)
{   //if the subset[i]'s parent isn't i
    //set equal to the prior generations
    (subsets[i].parent != i) ? subsets[i].parent = findCycle(subsets, subsets[i].parent) : i ;
    return subsets[i].parent;
}

void UnionNodes(struct subNet subset[], int& x, int& y)
{
    int rootOfx = findCycle(subset, x); //set x's root to the root of x
    int rootOfy = findCycle(subset, y); //set y's root to the root of y

    if (subset[rootOfx].rank < subset[rootOfy].rank){ //if the subset at x < y
        subset[rootOfx].parent = rootOfy; //set y as parent
      }else if (subset[rootOfx].rank > subset[rootOfy].rank){ //x > y
        subset[rootOfy].parent = rootOfx; //set x as parent of y
      }else // x = y
    {   subset[rootOfy].parent = rootOfx; //choose x at random
        subset[rootOfx].rank++; //increase it's rank
    }
}

/**The actual function to find the MST
   *\param foundMST is going to be the result
   *\param network is the list of all possible connections  */
void findMST(struct connectNode result[], std::vector<connectNode> &network, int &size){

      int j = 0;  // index for result
      int i = 0;  // index for edges

      struct subNet *subnets =  new struct subNet[size]; //reserve memory

      // create subnets
      for (int i = 0; i <= size; ++i)
      {
          subnets[i].parent = i;
          subnets[i].rank = 0;
      }

      while (j < size - 1)// looking for size - 1 edges
      {
          //take the smallest non double edge
          struct connectNode next_path = network[i];

          i++; //increment

          int x = findCycle(subnets, next_path.node1); //find cycle
          int y = findCycle(subnets, next_path.node2); //find cycle

          if (x != y) //if there is a cycle
          {
              result[j] = next_path; //this is a good addition
              UnionNodes(subnets, x, y); //add in what we found
              j++;
          }
          //otheriwise that sucked. boo
      }

}

/**Read in the network data line by line into an array
   *\param file is the file we are reading in from
   *\param input is the vector to put the network into
   *\param numberNodes is the amount of nodes in the network
   *\return error tracks if there was an error, what type, and where in the
                                                                          file.*/
exception_status readInNetwork(std::string file, std::vector<connectNode> &input, int &numberNodes){
  exception_status error;

    std::ifstream infile;

        infile.open(file);

        ///////////check file/////////
      if (!infile.is_open() || infile.fail()) {
          // set error
          return error.badCall("file_invalid"); // if the file didn't read, no need to continue.
      }

    infile >> numberNodes;//find initial node size
    infile >> std::ws; //strip initial whitespace

    int count = 0;
    char buf[128];
    input.reserve(numberNodes * numberNodes);

    while(!infile.eof()){
      int node1, node2, cost;

      count++;

      //---------node1--------
      infile.getline(buf, sizeof(buf), ' '); //read the current word up to space

      node1 = std::atoi(buf);

      //---------node2--------
      infile.getline(buf, sizeof(buf), ' '); //read the current word up to space

      node2 = std::atoi(buf);

      //---------cost--------
      infile.getline(buf, sizeof(buf)); //read the current word up to endline

      cost = std::atoi(buf);

      if(node1 != node2){ //avoid the loops
      input.emplace_back(node1, node2, cost);
      }

      infile >> std::ws;

    if (infile.fail()) {
        // set error
        error.which = count;
        return error.badCall("input_error_line_"); // if the file didn't read correctly, no need to continue.
    }
  }

  return error;
}
