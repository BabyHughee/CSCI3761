#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0); //maybe this works

using std::cout;
using std::cin;
using std::endl;
using std::cerr;


void error(std::string msg){
  cerr << (msg);
  cerr << "Errno: " << errno << endl;
  exit(1);
}


int main(int argc, char* argv[]){
    /* -------declare all the neccesary integers.------- */
  int listenSocket, msg_size;
  std::string inPort = "2121"; //this is the port
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





while(true){
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

  close(listenSocket);
}
    return 0;
}
