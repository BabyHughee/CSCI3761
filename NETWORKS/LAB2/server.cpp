#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <cstring>
#include <dirent.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <sstream>
#include <exception>

#define BACKLOG 3; //size of queue
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0); //maybe this works

using std::cout;
using std::cin;
using std::endl;
using std::cerr;



std::string getCatalog();
std::string getPwd();
void error(std::string msg);
void sigchld_handler(int s);


int main(int argc, char* argv[]) {
    /* -------declare all the neccesary integers.------- */
  int listenSocket, in_Connect, msg_size;
  socklen_t clientSize;
  char  buffer[256]; //this will hold the message recieved and sent.
  struct sockaddr_in serverAddress; //server info
  struct sockaddr_in clientAddress; //client info
  struct sigaction sa;


  if (argc != 2){
    cerr << "./server [port]" << endl;
    exit(1);
  }

/*----------------------------------------------------------------------------*/
/*-----------------------------Retrieve local address-------------------------*/
/*-*/ char* IPaddress;                                                     /*-*/
/*-*/ int hostName;                                                        /*-*/
/*-*/ struct hostent* thisHost;                                            /*-*/
/*-*/ char hostGetTemp[256];                                               /*-*/
/*-*/                                                                      /*-*/
/*-*/ hostName = gethostname(hostGetTemp, sizeof(hostGetTemp));            /*-*/
/*-*/ thisHost = gethostbyname(hostGetTemp);                               /*-*/
/*-*/ IPaddress = inet_ntoa(*((struct in_addr*)thisHost->h_addr_list[0])); /*-*/
/*-*/ cout << "||||||||||||||||||||||||||||||||||||||||||" << endl;        /*-*/
/*-*/ cout << "||||||NOW RUNNING FTP SERVER||||||||||||||" << endl;        /*-*/
/*-*/ cout << "||||||||||||||||||||||||||||||||||||||||||" << endl;        /*-*/
/*-*/ cout << ">Server is listening on: " << IPaddress << endl;            /*-*/
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
   printf(">Server: listening for incomming connections \n");

    /*---------SIG handling---------*/
   sa.sa_handler = sigchld_handler;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART;

   if (sigaction(SIGCHLD, &sa, NULL) == -1) {
         perror("sigaction");
         exit(1); }

while(true){ //threading loo[]
  clientSize = sizeof(clientAddress); //get client size

  in_Connect = accept(listenSocket,(struct sockaddr*) &clientAddress,&clientSize);
  if(in_Connect < 0) //Verify if succesful
    error("Error accepting"); //Well shoot.

    printf(">Server: got connection from %s\n", \
                 inet_ntoa(clientAddress.sin_addr)); //formatting

 if(!fork()){ //get the fork happening
       close(listenSocket);//---------------


  bool m_exit = false; //exit variable
  std::string temp; //handler variable
while(!m_exit){

   /* ---------Get Message--------- */
  bzero(buffer,256);

  if((msg_size = read(in_Connect, buffer, 255)) < 0) //receive message
    error("Error reading");

   cout << ">Client"<< getpid() << ": " << buffer << endl; //show client with pid

///////////////////////////////
try{
  if(strncmp(buffer,"catalog",7) == 0){
    temp =  getCatalog();
  }
  else if(strncmp(buffer,"spwd",4) == 0){
    temp = getPwd();
  }
  else if(strncmp(buffer,"bye",3) == 0){
    temp = "File copy server is down!";
    m_exit = true;
  }
  else if(strncmp(buffer,"download",8) == 0){
    temp = "downloaded";
        ////////////////////////////////FILE SENDER////////////////////////////////////

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

                            if((msg_size = write(in_Connect, sendFailure, sizeof(sendFailure))) < 0) //not a success
                              error("Error writing");

                            throw("File_Not_Found");
                          }else{

                            char sendSuccess[] = "Yes";

                            if((msg_size = write(in_Connect, sendSuccess, sizeof(sendSuccess))) < 0) //not a success
                              error("Error writing");
                          }
        //////////////////////////////////////check availability////////////////////////

        int fileSize;

        fseek(fd, 0L, SEEK_END); //find
        fileSize = ftell(fd); //the
        rewind(fd); //filesize

        std::string sizeAccept = std::to_string(fileSize); //prepare size for sending

        // cout << fileSize << endl;
        if((msg_size = write(in_Connect, sizeAccept.c_str(), 255) < 0)) //Send size
          error("Error writing");


        int totalSize = 0;
        msg_size = 0;
        char fileBuffer[1024]; //save size

        do{
          bzero(fileBuffer, 1024);
          fread( fileBuffer, sizeof(fileBuffer), 1, fd); //read in  the file

          if((msg_size = write(in_Connect, fileBuffer, sizeof(fileBuffer))) < 0) //Send the file
            error("Error writing");

            totalSize += msg_size;
        }while((totalSize < fileSize) && !(msg_size <= 0));

        fclose(fd); //close the file
        ///////////////////////////////////////////////////////////////////////////////
  }else if(strncmp(buffer,"upload",6) == 0){
      temp = "uploaded";
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
                                if((msg_size = read(in_Connect, avalabilityChecker, sizeof(avalabilityChecker) + 1)) < 0) //read status
                                  error("Error reading");
                                          if(strncmp(avalabilityChecker, "No",2) == 0){
                                            throw("Download_File_Not_Found");
                                          }else{
                                            /*DO NOTHING*/
                                          }
                        //////////////////////////////////////read availability////////////////////////


                        FILE* fp = fopen(output.c_str(), "wb+"); //open file in write binary

                        if((msg_size = read(in_Connect, buffer, 255)) < 0) //read size
                          error("Error reading");


                        // cout << atoi(buffer) << endl;
                        int fileSize = atoi(buffer);
                        int totalSize = 0;
                        msg_size = 1;
                        char fileBuffer[1024]; //save size

                        // cout << fileSize;

                        do{
                          // cout << totalSize << endl;

                          if((msg_size = read(in_Connect, fileBuffer, 1024)) < 0) //read file
                            error("Error reading");


                          fwrite(fileBuffer, 1, msg_size, fp); //save file

                          totalSize += msg_size;
                        }while((totalSize < fileSize) && !(msg_size <= 0));

                        fclose(fp); //close
      ////////////////////////////////////////////////////////////////////////////////
  }else {
    temp = "**invalid command**";}

}catch(const char* fileFailure){temp = "done goofed";}
    /* ---------Return Message--------- */

   if((msg_size = write(in_Connect, temp.c_str(), temp.size())) < 0) //Send message
     error("Error writing");
}


            printf("Server: close connection from %s\n", \
                   inet_ntoa(clientAddress.sin_addr)); //Client disconnect message
            cout << "------------------------------>Client"<<getpid() << endl;
            close(in_Connect); // close the connection
            exit(0);
}

close(in_Connect); //close socket
}

   close(listenSocket); //close socket

    return 0;
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
  directory.pop_back(); //Remove last new line
  closedir(dir); //close the stream


   return directory; //and return
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

void error(std::string msg){ //error handler
  cerr << (msg) << endl;
  exit(1);
}

void sigchld_handler(int s) //sig handler
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}
