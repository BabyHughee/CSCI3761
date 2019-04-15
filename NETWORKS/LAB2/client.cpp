#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>
#include <string>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sstream>
#include <exception>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0); //maybe this works

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

std::string executeCommand(std::string);
void error(std::string msg);
std::string getPwd();


int main(int argc, char* argv[]){
    /* -------declare all the neccesary integers.------- */
  int listenSocket, msg_size;
  // std::string inPort = "2121"; //this is the port
  char  buffer[256]; //this will hold the message recieved and sent.
  struct addrinfo* serverAddress; //server info
  struct addrinfo hints; //used to specify TCP

  if (argc != 3){
    cerr << "./client [server IP] [port]" << endl;
    exit(1);
  }


    /* ---------Open socket--------- */
  if((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    error("Error opening socket");

  bzero((char*) &hints, sizeof(hints)); //clearBuffer

  hints.ai_family = AF_INET;  //specify TCP

  /* ---------Get Server Info--------- */
  if(getaddrinfo(argv[1], argv[2], &hints, &serverAddress) < 0)
    error("Error finding host");

    /* ---------connect to server--------- */
  cerr << "Connecting to: " << inet_ntoa(((struct sockaddr_in*) serverAddress->ai_addr)->sin_addr) << endl;

  if (connect(listenSocket, serverAddress->ai_addr, sizeof(struct sockaddr)) < 0)
     error("\nError connecting\n");

  cout << "Welcome to the FTP server\n for list of commands type \'help\'" << endl;


bool m_exit = false; //exit variable
while(!m_exit){
    /* ---------Send--------- */
  bzero(buffer, 256);

  // cin.clear();
  cout << ">";
  std::cin.getline(buffer, 255, '\n'); //get the command from commandline


  if(strncmp(buffer,"pwd",3) == 0){ //client working directory
    cout << getPwd() << endl;

  }else if(strncmp(buffer,"ls",2) == 0){ //client directory contents
    cout << executeCommand(buffer) << endl;

  }else if(strncmp(buffer,"help",4) == 0){ //command list

    cout << "ls [options]  - Display all the file names under current directory\n"
         << "pwd           - Display current directory information\n"
         << "catalog       - Display the all file names under current server directory\n"
         << "spwd          - Display current server directory information\n"
         << "download source-filename dest-filename  \n"
         << "              - Download file from server\n"
         << "upload source-filename dest-filename  \n"
         <<  "              - Upload file from server\n"
         <<  "bye           - Disconnect from server\n";
  }else{ //I am so sorry for this spaghetti code


  //if it was none of the above the server is involved
  if((msg_size = write(listenSocket, buffer, 255)) < 0)
    error("Error writing");

try{
  if(strncmp(buffer,"download",8) == 0){
////////////////////////////////FILE RECIEVER////////////////////////////////////


                  std::string downloadcmd[3];

                  std::stringstream split(buffer); //parse command into components
                  for(int i = 0; i < 3; i++){
                    split >> downloadcmd[i];
                  }
                  bzero(buffer, 256);

                  std::string output = downloadcmd[2];

                  //////////////////////////////////////read availability////////////////////////
                  char avalabilityChecker[20];
                          if((msg_size = read(listenSocket, avalabilityChecker, sizeof(avalabilityChecker) + 1)) < 0) //read status
                            error("Error reading");
                                    if(strncmp(avalabilityChecker, "No",2) == 0){
                                      throw("Download_File_Not_Found");
                                    }else{
                                      /*DO NOTHING*/
                                    }
                  //////////////////////////////////////read availability////////////////////////


                  FILE* fp = fopen(output.c_str(), "wb+"); //open file in write binary

                  if((msg_size = read(listenSocket, buffer, 255)) < 0) //read size
                    error("Error reading");


                  // cout << atoi(buffer) << endl;
                  int fileSize = atoi(buffer);
                  int totalSize = 0;
                  msg_size = 1;
                  char fileBuffer[1024]; //save size

                  // cout << fileSize;

                  do{
                    // cout << totalSize << endl;

                    if((msg_size = read(listenSocket, fileBuffer, 1024)) < 0) //read file
                      error("Error reading");


                    fwrite(fileBuffer, 1, msg_size, fp); //save file

                    totalSize += msg_size;
                  }while((totalSize < fileSize) && !(msg_size <= 0));

                  fclose(fp); //close
////////////////////////////////////////////////////////////////////////////////
  }
  else if(strncmp(buffer,"upload",6) == 0){
    ////////////////////////////////FILE SENDER////////////////////////////////////
    sleep(1);
    std::string downloadcmd[3];

    std::stringstream split(buffer); //parse command into sections
    for(int i = 0; i < 3; i++){
      split >> downloadcmd[i];
      }

    bzero(buffer,256);

    std::string filename = downloadcmd[1];

    FILE *fd = fopen(filename.c_str(), "rb"); //read that binary

    //////////////////////////////////////check availability////////////////////////
                      if(fd == NULL){
                        char sendFailure[] = "No";
                        fclose(fd); //close the file

                        if((msg_size = write(listenSocket, sendFailure, sizeof(sendFailure))) < 0) //not a success
                          error("Error writing");

                        throw("File_Not_Found");
                      }else{

                        char sendSuccess[] = "Yes";

                        if((msg_size = write(listenSocket, sendSuccess, sizeof(sendSuccess))) < 0) //not a success
                          error("Error writing");
                      }
    //////////////////////////////////////check availability////////////////////////

    int fileSize;

    fseek(fd, 0L, SEEK_END); //find
    fileSize = ftell(fd); //the
    rewind(fd); //filesize

    std::string sizeAccept = std::to_string(fileSize); //prepare size for sending

    // cout << fileSize << endl;
    if((msg_size = write(listenSocket, sizeAccept.c_str(), 255) < 0)) //Send size
      error("Error writing");


    int totalSize = 0;
    msg_size = 0;
    char fileBuffer[1024]; //save size

    do{
      bzero(fileBuffer, 1024);
      fread( fileBuffer, sizeof(fileBuffer), 1, fd); //read in  the file

      if((msg_size = write(listenSocket, fileBuffer, sizeof(fileBuffer))) < 0) //Send the file
        error("Error writing");

        totalSize += msg_size;
    }while((totalSize < fileSize) && !(msg_size <= 0));

    fclose(fd); //close the file
    ///////////////////////////////////////////////////////////////////////////////
  }
  else if(strncmp(buffer,"bye",3) == 0){ //set exit
    m_exit = true;
  }

}catch(const char* failMessage){ cout << failMessage << endl;}
    /* ---------Recieve--------- */

  if((msg_size = read(listenSocket, buffer, 256)) < 0) //read handler from server
    error("Error reading");

  cout << ">" << "Server: " << buffer << endl; //output results

    }
  }

  close(listenSocket); //close up shop


    return 0;
}


/** Executes ls command with options and returns results
  \@ Param command command to execute
  \@ Return a string with results of ls */
std::string executeCommand(std::string command){
  char result[256];
  /*create custom deleting pointer to the pipe from command that is outputting
                                                           to the commandline*/
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);

  //get the results of the command from the child
  while (fgets(result, 128, pipe.get()) != nullptr) {
        printf("%s", result); //put results into the return string
    }

    //remove last '\n' from result
  for(int i = 0; i < sizeof(result); i++){
    if(result[i] == '\0') //if we reach terminating character
        {result[i-1] = '\0';} //the previous character (final '\n') now is '\0'
  }

   return result; //and return
}

/** Finds the current working directory and return it as a string
  \@ Param Takes nothing
  \@ Return a string with the current path*/
std::string getPwd(){
  char cwd[4096];
  getcwd(cwd, sizeof(cwd)); //get the current working directory
  std::string directory = cwd; //set directory to it
  return directory; //and return
}



void error(std::string msg){ //error handler
  cerr << (msg);
  cerr << "Errno: " << errno << endl;
  exit(1);
}
