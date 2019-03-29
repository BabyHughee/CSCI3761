#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <netdb.h>

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
  int listenSocket, msg_size;
  // socklen_t clientSize;
  int inPort = 2121;//2121; //this is the port and also my student ID
  char  buffer[256]; //this will hold the message recieved and sent.
  // struct sockaddr_in serverAddress; //server
  struct addrinfo* serverAddress; //server
  struct addrinfo hints; //server
  int server;

    /* ---------Manage socket jazz--------- */
  listenSocket = socket(AF_INET, SOCK_STREAM, 0);

  if(listenSocket < 0) //Verify if succesful
    error("Error opening socket"); //Well shoot.


    /* ---------Get that stuffs told other stuffs--------- */
  hints.ai_family = AF_INET;  //declare addr family
   /*------------------------------------------------------*/

  std::string ucdenver = "132.194.186.166";

  server = getaddrinfo("csegrid.ucdenver.pvt", "2121", &hints, &serverAddress);

  if(server < 0) //Verify if succesful
    error("Error finding host"); //Well shoot.

  bzero((char*) &serverAddress, sizeof(serverAddress)); //clearBuffer



    /* ---------Tie it up in a bow--------- */
  if (connect(listenSocket, serverAddress->ai_addr, serverAddress->ai_addrlen))
     error("\nError connecting\n"); //Well shoot.
     // error("\nWhat\nda\nfuck...\n"); //Well shoot.


    /* ---------Listen--------- */
  cout << "Please enter a message: ";
  bzero(buffer, 256);
  std::cin.getline(buffer, 255, '\n');
  msg_size = write(listenSocket, buffer, 255);
  if(msg_size < 0) //Verify if succesful
    error("Error writing"); //Well shoot.

  bzero(buffer,256);
    msg_size = read(listenSocket, buffer, 255);
  if(msg_size < 0) //Verify if succesful
    error("Error reading"); //Well shoot.

  cout << "Server: " << buffer << endl;

    return 0;
}
