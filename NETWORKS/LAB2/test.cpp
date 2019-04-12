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
std::string getSpwd();
void error(std::string);

int main(){

//SERVER SIDE
std::string filename = "README";
FILE *fd = fopen(filename.c_str(), "rb");
int fileSize;

fseek(fd, 0L, SEEK_END);
fileSize = ftell(fd);
rewind(fd);

char buffer[fileSize];

std::string sizeAccept = std::to_string(fileSize); //prepare message

fread( buffer , fileSize, 1 , fd);



//CLIENT SIDE
std::string output = "testOut";

FILE* fp = fopen(output.c_str(), "wb");

fwrite(&buffer, 1, sizeof(buffer), fp);

    fclose(fd);


    // std::string directory = getCatalog();
    //
    // cout << directory << endl;
    //
    // getSpwd();

    return 0;
}

void error(std::string msg){
  cerr << (msg);
  exit(1);
}


/** Makes a list of every file in the working directory seperated by new lines
  \@ Param Takes nothing
  \@ Return a string with results of ls **/
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


/** Finds the current working directory and return it as a string
  \@ Param Takes nothing
  \@ Return a string with the current path**/
std::string getSpwd(){
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd)); //get the current working directory
  std::string directory = cwd; //set directory to it
  return directory; //and return
}
