#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <cstring>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0); //maybe this works

using std::cout;
using std::cin;
using std::endl;
using std::cerr;


void error(std::string msg){
  cerr << (msg);
  exit(1);
}


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
  serverAddress.sin_addr.s_addr = "127.0.0.1";  //Set this to the local IP

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
  cout << "The message is: " << buffer << endl;

    return 0;
}
