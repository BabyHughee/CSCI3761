#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <dirent.h>

#define bzero(b,len) (memset((b), '\0', (len)), (void) 0); //maybe this works

using std::cout;
using std::cin;
using std::endl;
using std::cerr;


int main(){
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


     cout << directory << endl;

    return 0;
}
