#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <dirent.h>
#include <arpa/inet.h>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0); //maybe this works

using std::cout;
using std::cin;
using std::endl;
using std::cerr;


std::string serveClient(char*);
std::string getCatalog();
std::string getSpwd();
void error(std::string msg);


int main(int argc, char* argv[]) {
    /* -------declare all the neccesary integers.------- */
  int listenSocket, in_Connect, msg_size;
  socklen_t clientSize;
  char  buffer[256]; //this will hold the message recieved and sent.
  struct sockaddr_in serverAddress; //server info
  struct sockaddr_in clientAddress; //client info


  if (argc != 2){
    cerr << "./server [port]" << endl;
    exit(1);
  }

/*----------------------------------------------------------------------------*/
/*-----------------------------Retrieve local address-------------------------*/
/*-*/ char* IPaddress;                                                     /*-*/
/*-*/ int hostName;                                                        /*-*/
/*-*/ struct hostent* thisHost;                                            /*-*/
/*-*/ char temp[256];                                                      /*-*/
/*-*/                                                                      /*-*/
/*-*/ hostName = gethostname(temp, sizeof(temp));                          /*-*/
/*-*/ thisHost = gethostbyname(temp);                                      /*-*/
/*-*/ IPaddress = inet_ntoa(*((struct in_addr*)thisHost->h_addr_list[0])); /*-*/
/*-*/ cout << "Server is listening on: " << IPaddress << endl;             /*-*/
/*-------------------(Thanks to GeeksforGeeks for this method)----------------*/
/*-------------------Local address retrieved----------------------------------*/
/*----------------------------------------------------------------------------*/

    /* ---------Open socket--------- */
  if((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    error("Error opening socket");

    bzero((char*) &serverAddress, sizeof(serverAddress)); //clearBuffer

    /* ---------Load up details--------- */
  serverAddress.sin_family = AF_INET;  //declare addr family
  serverAddress.sin_port = htons(atoi(argv[1]));  //declare Port number
  serverAddress.sin_addr.s_addr = INADDR_ANY;  //Set this to the local IP 132.194.186.55

    /* ---------Bind the server--------- */
  if (bind(listenSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
     error("Error binding");





    /* ---------Listen--------- */
  listen(listenSocket, 5);

  clientSize = sizeof(clientAddress);
  in_Connect = accept(listenSocket,(struct sockaddr*) &clientAddress,&clientSize);
  if(in_Connect < 0) //Verify if succesful
    error("Error accepting"); //Well shoot.

   /* ---------Get Message--------- */
  bzero(buffer,256);

  if((msg_size = read(in_Connect, buffer, 255)) < 0) //receive message
    error("Error reading");

  cout << "Client: " << buffer << endl; //show recieved message

  /* ---------Return Message--------- */
 // bzero(buffer,256);

std::string returnMessage = serveClient(buffer); //prepare message

 if((msg_size = write(in_Connect, returnMessage.c_str(), 255)) < 0) //Send message
   error("Error writing");

   close(listenSocket);

    return 0;
}


/** Take in the requests of each server and handle them as needed
  \@ Param msg is the message sent from the client
  \@ Return a string containing the response   */
std::string serveClient(char* msg){
  if(strncmp(msg,"ls",2) == 0){
    return getCatalog();
  }
  if(strncmp(msg,"pwd",3) == 0){
    return getSpwd();
  }

  return "fail";
}




/** Makes a list of every file in the working directory seperated by new lines
  \@ Param Takes nothing
  \@ Return a string with results of ls */
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
  \@ Return a string with the current path*/
std::string getSpwd(){
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd)); //get the current working directory
  std::string directory = cwd; //set directory to it
  return directory; //and return
}

void error(std::string msg){
  cerr << (msg);
  exit(1);
}
