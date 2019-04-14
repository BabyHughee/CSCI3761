#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
// #include <cstring>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
// #include <dirent.h>
// #include <array>
// #include <memory>
// #include <cstdio>
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


bool m_exit = false;
while(!m_exit){
    /* ---------Send--------- */
  bzero(buffer, 256);

  // cin.clear();
  cout << ">";
  std::cin.getline(buffer, 255, '\n');


  if(strncmp(buffer,"pwd",3) == 0){
    cout << getPwd() << endl;
  }else if(strncmp(buffer,"ls",2) == 0){
    cout << executeCommand(buffer) << endl;
  }else if(strncmp(buffer,"help",4) == 0){
    cout << "ls [options]  - Display all the file names under current directory\n"
         << "pwd           - Display current directory information\n"
         << "catalog       - Display the all file names under current server directory\n"
         << "spwd          - Display current server directory information\n"
         << "download source-filename dest-filename  \n"
         << "              - Download file from server\n"
         << "upload source-filename dest-filename  \n"
         <<  "              - Upload file from server\n";
  }else{ //I am so sorry for this spaghetti code


  if((msg_size = write(listenSocket, buffer, 255)) < 0) //send message
    error("Error writing");

// try{
  if(strncmp(buffer,"download",8) == 0){
                  ////////////////////////////////FILE RECIEVER////////////////////////////////////
                  std::string downloadcmd[3];

                  std::stringstream split(buffer);
                  for(int i = 0; i < 3; i++){
                    split >> downloadcmd[i];
                  }

                  bzero(buffer, 256);

                  std::string output = downloadcmd[2];

                  FILE* fp = fopen(output.c_str(), "wb");

                  if((msg_size = read(listenSocket, buffer, 255)) < 0) //read server's response
                    error("Error reading");

                  // cout << atoi(buffer) << endl;
                  int fileSize = atoi(buffer);
                  char fileBuffer[fileSize];


                  if((msg_size = read(listenSocket, fileBuffer, fileSize + 1)) < 0) //read server's response
                    error("Error reading");

                  fwrite(fileBuffer, 1, fileSize, fp);

                  fclose(fp);
                  ////////////////////////////////////////////////////////////////////////////////
  }
  else if(strncmp(buffer,"upload",6) == 0){
                  ////////////////////////////////FILE SENDER////////////////////////////////////
                  bzero(buffer,256);

                  std::string uploadcmd[3];

                  std::stringstream split(buffer);
                  for(int i = 0; i < 3; i++){
                    split >> uploadcmd[i];
                  }

                  std::string filename = uploadcmd[1];

                  FILE *fd = fopen(filename.c_str(), "rb");

                  int fileSize;

                  fseek(fd, 0L, SEEK_END);
                  fileSize = ftell(fd);
                  rewind(fd);

                  char fileBuffer[fileSize];

                  std::string sizeAccept = std::to_string(fileSize); //prepare message

                  // cout << fileSize << endl;

                  if((msg_size = write(listenSocket, sizeAccept.c_str(), 255) < 0)) //Send message
                    error("Error writing");

                  fread( fileBuffer , fileSize, 1 , fd);

                 if((msg_size = write(listenSocket, fileBuffer, fileSize)) < 0) //Send message
                   error("Error writing");

                    fclose(fd);
                  ///////////////////////////////////////////////////////////////////////////////
  }
  else if(strncmp(buffer,"exit",4) == 0){
    m_exit = true;
  }

// }catch(std::string fileFail)

    /* ---------Recieve--------- */
  bzero(buffer,256);

  if((msg_size = read(listenSocket, buffer, 256)) < 0) //read server's response
    error("Error reading");

  cout << ">" << "Server: " << buffer << endl;

    }
  }

  close(listenSocket);


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
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd)); //get the current working directory
  std::string directory = cwd; //set directory to it
  return directory; //and return
}



void error(std::string msg){
  cerr << (msg);
  cerr << "Errno: " << errno << endl;
  exit(1);
}
