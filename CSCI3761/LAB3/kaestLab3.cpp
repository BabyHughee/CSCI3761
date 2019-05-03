#include "kaestLab3.h"



/**A Utitlity function for the merge sort
   *\param left is the left segmented node list
   *\param right is the right segmented node list
   *\return merged is the merging of the left and right node lists */
std::vector<connectNode> SBWmerge(std::vector<connectNode> left, std::vector<connectNode> right)
{
   std::vector<connectNode> merged;
   while ((int)left.size() > 0 || (int)right.size() > 0) { //we havent processed everything

      if ((int)left.size() > 0 && (int)right.size() > 0) { //if each vector still has stuffs

         if ((int)left.front().cost <= (int)right.front().cost) { //if the front of left is less that front of right
            merged.push_back(left.front()); //take the smaller one ( left )
            left.erase(left.begin());    } //and delete
          else{
            merged.push_back(right.front());  //take the smaller one ( right )
            right.erase(right.begin());  } //and delete

      }
      else if ((int)left.size() > 0) { //if the left one still has stuffs (and the right is empty)

            for (int i = 0; i < (int)left.size(); i++){   merged.push_back(left[i]);  } //put in the last of the left
            break;

      }
      else if ((int)right.size() > 0) { //if the right one still has stuffs (and the left is empty)
            for (int i = 0; i < (int)right.size(); i++){   merged.push_back(right[i]);  } //put in the last of the right
            break;
      }
   }
   return merged; //return the merged boi
}








/**Sort the vector structs by minimum weight to maximum using merge sort
   *\param toSort is the vector that holds the weights
   *\return result is the sorted array */
std::vector<connectNode> sortByWeight(std::vector<connectNode> &toSort){

     if (toSort.size() <= 1) //if there is nothing we just eturn it all
        return toSort;

     std::vector<connectNode> sorted, left, right; //we need the sorted one and the two halves

     int middle = ((int)toSort.size()+ 1) / 2; //where are we splitting this one

     //construct the left list (initial list from beginning to the middle)
     for (int i = 0; i < middle; i++) {   left.push_back(toSort[i]);  }

     //construct the right list (initial list from middle to the end
     for (int i = middle; i < (int)toSort.size(); i++){    right.push_back(toSort[i]);   }

     left = sortByWeight(left); //send the left back through (want to get to smallest vector)
     right = sortByWeight(right); //send the right back through (want to get to smallest vector)
     sorted = SBWmerge(left, right); //merge those two lists

     return sorted; //return what was accomplished
}

/**Function to find a set of i
  *\param subset is our list of good connections
  *\param i is to be found
  *\return return the parent of i */
int find(struct subNet subsets[], int& i)
{
    if (subsets[i].parent != i) //if the subset[i]'s parent isn't i
        subsets[i].parent = find(subsets, subsets[i].parent); //set equal to the prior generations

    return subsets[i].parent;
}

void Union(struct subNet subset[], int& x, int& y)
{
    int rootOfx = find(subset, x); //set x's root to the root of x
    int rootOfy = find(subset, y); //set y's root to the root of y

    if (subset[rootOfx].rank < subset[rootOfy].rank) //if the subset at x < y
        subset[rootOfx].parent = rootOfy; //set y as parent
    else if (subset[rootOfx].rank > subset[rootOfy].rank) //x > y
        subset[rootOfy].parent = rootOfx; //set x as parent of y

    else // x = y
    {
        subset[rootOfy].parent = rootOfx; //choose x at random
        subset[rootOfx].rank++; //increase it's rank
    }
}

/**The actual function to find the MST
   *\param foundMST is going to be the result
   *\param network is the list of all possible connections  */
void findMST(struct connectNode result[], std::vector<connectNode> &network, int &size){

      int e = 0;  // index for result
      int i = size;  // index for edges

      //prepare memory
      struct subNet *subnets =  new struct subNet[size];

      // create subnets
      for (int i = 0; i <= size; ++i)
      {
          subnets[i].parent = i;
          subnets[i].rank = 0;
      }

      while (e < size - 1)// looking for size - 1 edges
      {
          //take the smallest non double edge
          struct connectNode next_path = network[i];

          i++; //increment

          int x = find(subnets, next_path.node1); //find cycle
          int y = find(subnets, next_path.node2); //find cycle

          if (x != y) //if there is a cycle
          {
              result[e] = next_path; //this is a good addition
              e++;
              Union(subnets, x, y); //add in what we found
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
        error.which = count;
        return error.badCall("input_error_line_"); // if the file didn't read correctly, no need to continue.
    }
  }

  return error;
}
