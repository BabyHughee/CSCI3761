#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <dirent.h>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0); //maybe this works

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

std::string getCatalog();
void error(std::string msg);


int main(){
    /* -------declare all the neccesary integers.------- */
  int listenSocket, in_Connect, msg_size;
  socklen_t clientSize;
  int inPort = 2414; //this is the port and also my student ID
  char  buffer[256]; //this will hold the message recieved and sent.
  struct sockaddr_in serverAddress; //server
  struct sockaddr_in clientAddress; //client

    /* ---------Manage socket jazz--------- */
  listenSocket = socket(AF_INET, SOCK_STREAM, 0);

  if(listenSocket < 0) //Verify if succesful
    error("Error opening socket"); //Well shoot.

  bzero((char*) &serverAddress, sizeof(serverAddress)); //clearBuffer

    /* ---------Get that server stuffs told other stuffs--------- */
  serverAddress.sin_family = AF_INET;  //declare addr family
  serverAddress.sin_port = htons(inPort);  //declare Port number
  serverAddress.sin_addr.s_addr = "132.194.186.55";//INADDR_ANY;  //Set this to the local IP

    /* ---------Tie it up in a bow--------- */
  if (bind(listenSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
     error("Error binding"); //Well shoot.

    /* ---------Listen--------- */
  listen(listenSocket, 5);

  clientSize = sizeof(clientAddress);
  in_Connect = accept(listenSocket,(struct sockaddr*) &clientAddress,&clientSize);
  if(in_Connect < 0) //Verify if succesful
    error("Error accepting"); //Well shoot.

   /* ---------Get Message--------- */
  bzero(buffer,256);
  msg_size = read(in_Connect, buffer, 255);
  if(msg_size < 0) //Verify if succesful
    error("Error reading"); //Well shoot.
  cout << "Client: " << buffer << endl;

  /* ---------Return Message--------- */
 bzero(buffer,256);
char returnMessage[256] = "Hello Client.";
std::string catalogue = getCatalog();
 msg_size = write(in_Connect, catalogue.c_str(), 255);
 if(msg_size < 0) //Verify if succesful
   error("Error writing"); //Well shoot.

    return 0;
}


void error(std::string msg){
  cerr << (msg);
  exit(1);
}



std::string getCatalog(){
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  std::string directory;

  DIR *dir;

  if((dir = opendir(cwd)) == NULL){ cout << "CWD_NOT_FOUND";  }

  struct dirent* i;

  while((i = readdir(dir)) != NULL ){
      directory.append(i->d_name);
      directory.append("\n");
  }

  closedir(dir);


   return directory;
}
