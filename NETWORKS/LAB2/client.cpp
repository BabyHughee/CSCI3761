#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <netdb.h>


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
  int listenSocket, msg_size;
  // socklen_t clientSize;
  int inPort = 2414; //this is the port and also my student ID
  char  buffer[256]; //this will hold the message recieved and sent.
  struct sockaddr_in serverAddress; //server
  struct hostent *server;

    /* ---------Manage socket jazz--------- */
  listenSocket = socket(AF_INET, SOCK_STREAM, 0);

  if(listenSocket < 0) //Verify if succesful
    error("Error opening socket"); //Well shoot.

  server = gethostbyname("csegrid.ucdenver.pvt");
  if(server == NULL) //Verify if succesful
    error("Error finding host"); //Well shoot.

  memset((char*) &serverAddress, 0, sizeof(serverAddress)); //clearBuffer

    /* ---------Get that stuffs told other stuffs--------- */
  serverAddress.sin_family = AF_INET;  //declare addr family
  bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
  serverAddress.sin_port = htons(inPort);  //declare Port number

    /* ---------Tie it up in a bow--------- */
  if (connect(listenSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
     error("Error connecting"); //Well shoot.

    /* ---------Listen--------- */
  cout << "Please enter a message: ";
  memset(buffer, 0, 256);
  std::cin.getline(buffer, 255, '\n');

  msg_size = write(listenSocket, buffer, 255);
  if(msg_size < 0) //Verify if succesful
    error("Error writing"); //Well shoot.

  memset(buffer, 0, 256);
    msg_size = read(listenSocket, buffer, 255);
  if(msg_size < 0) //Verify if succesful
    error("Error writing"); //Well shoot.

  cout << "The message is: " << buffer << endl;

    return 0;
}
