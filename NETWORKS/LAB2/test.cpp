#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <dirent.h>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

std::string getCatalog();
void error(std::string);

int main(){
    std::string directory = getCatalog();

    cout << directory << endl;

    return 0;
}

void error(std::string msg){
  cerr << (msg);
  exit(1);
}


/** Makes a list of every file in the working directory seperated by new lines
  \@ Param Takes nothing
  \@ Return a string **/
std::string getCatalog(){
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd)); //get the current working directory
  std::string directory;

  DIR *dir; //prepare to open a stream.

  if((dir = opendir(cwd)) == NULL){
      cout << "CWD_NOT_FOUND";
      return "CWD_NOT_FOUND";
    } //if it doesnt exist output error and return error.

  struct dirent* i;

  while((i = readdir(dir)) != NULL ){ //otherwise
      directory.append(i->d_name); //add the new item to the string
      directory.append("\n"); //and add a new line
  }

  closedir(dir); //close the stream


   return directory; //and return
}
