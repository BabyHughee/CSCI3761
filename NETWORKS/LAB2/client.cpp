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


int main(int argc, char* argv[]){
    /* -------declare all the neccesary integers.------- */
  int listenSocket, msg_size;
  std::string inPort = "2121"; //this is the port
  char  buffer[256]; //this will hold the message recieved and sent.
  struct addrinfo* serverAddress; //server info
  struct addrinfo hints; //used to specify TCP





    /* ---------Open socket--------- */
  if((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    error("Error opening socket");

  hints.ai_family = AF_INET;  //specify TCP

  /* ---------Get Server Info--------- */
  if(getaddrinfo("127.0.0.1", inPort.c_str(), &hints, &serverAddress) < 0)
    error("Error finding host");

    /* ---------connect to server--------- */
  if (connect(listenSocket, serverAddress->ai_addr, sizeof(struct sockaddr)) < 0)
     error("\nError connecting\n");






    /* ---------Send--------- */
  bzero(buffer, 256);

  cout << "Please enter a message: ";
  std::cin.getline(buffer, 255, '\n');


  if((msg_size = write(listenSocket, buffer, 255)) < 0) //send message
    error("Error writing");

    /* ---------Recieve--------- */
  bzero(buffer,256);

  if((msg_size = read(listenSocket, buffer, 255)) < 0) //read server's response
    error("Error reading");

  cout << "Server: " << buffer << endl;

    return 0;
}





















// #include <iostream>
// #include <stdio.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <netinet/in.h>
// #include <unistd.h>
// #include <string>
// #include <cstring>
// #include <netdb.h>
//
// #define bzero(b,len) (memset((b), '\0', (len)), (void) 0); //maybe this works
//
// using std::cout;
// using std::cin;
// using std::endl;
// using std::cerr;
//
//
// void error(std::string msg){
//   cerr << (msg);
//   exit(1);
// }
//
//
// int main(int argc, char *argv[]) {
//     /* -------declare all the neccesary integers.------- */
//   int listenSocket, msg_size;
//   // socklen_t clientSize;
//   int inPort = 5984;//2121; //this is the port and also my student ID
//   char  buffer[256]; //this will hold the message recieved and sent.
//   // struct sockaddr_in serverAddress; //server
//   struct sockaddr_in serverAddress; //server
//   // struct addrinfo hints; //server
//   struct hostent* server;
//
//     /* ---------Manage socket jazz--------- */
//   listenSocket = socket(AF_INET, SOCK_STREAM, 0);
//
//   if(listenSocket < 0) //Verify if succesful
//     error("Error opening socket"); //Well shoot.
//
//
//    /*------------------------------------------------------*/
//
//    // if (argc != 2) {
//    //   cerr << "usage: client hostname\n";
//    //   exit (1);
//    //   }
//
//   // server = gethostbyname(argv[1]);
//
//   server = gethostbyname("csegrid.ucdenver.pvt");
//
//   if(server == NULL) //Verify if succesful
//     error("Error finding host"); //Well shoot.
//
//   bzero((char*) &serverAddress, sizeof(serverAddress)); //clearBuffer
//
//   serverAddress.sin_family = AF_INET; /* interp’d by host */
//   serverAddress.sin_port = htons (inPort);
//   serverAddress.sin_addr = *((struct in_addr*)server->h_addr);
//
//     /* ---------Tie it up in a bow--------- */
//   if (connect(listenSocket,(struct sockaddr*) &serverAddress, sizeof(struct sockaddr)) == -1){
//      error("\nError connecting\n"); //Well shoot.
//      // error("\nWhat\nda\nfuck...\n"); //Well shoot.
//    }
//
//
//     /* ---------Listen--------- */
//   cout << "Please enter a message: ";
//   bzero(buffer, 256);
//   std::cin.getline(buffer, 255, '\n');
//   msg_size = write(listenSocket, buffer, 255);
//   if(msg_size < 0) //Verify if succesful
//     error("Error writing"); //Well shoot.
//
//   bzero(buffer,256);
//     msg_size = read(listenSocket, buffer, 255);
//   if(msg_size < 0) //Verify if succesful
//     error("Error reading"); //Well shoot.
//
//   cout << "Server: " << buffer << endl;
//
//     return 0;
// }
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
