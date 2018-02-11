#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "worker_queue.h"

#define WRITE 1


int main(int argc,char** argv){
    int fdp[2],i=0,N=3,waiting=0,job_id=1,status=200;
    DIR *dirp;
    char* message[1024];
    struct dirent *element;
    struct stat stbuf;

    
    /*prwta dimiourgw pipe epikoinwnias metaxi listener ,manager*/
    if(mkfifo("listener_pipe",0666)==-1){
            perror("manager,failed to create pipe:");
            exit(1);
    }
    
    /*Prospatheia na grapsw ston pipe*/

    fdp[1]=open("listener_pipe", O_WRONLY | O_NONBLOCK);
    i=0;
    
    /*thelw na kanw dup etsi oti grafei to inotifywait adi gia na to grafei sto stdout na to grafei sto pipe*/
    int c1 = dup2(fdp[WRITE] ,1); /*redirect tou stdout sto write tou listener pipe*/

    execl("/usr/bin/inotifywait","inotifywait", "-m","-e","create",".", NULL);
    
/*
    while( read(fdp,&(message[i]),1)){
        i++;
    }
    dirp = opendir(message);
    
    execv(inotifywait ,-e dirp, -e create);
    while( (element = readdir(dirp)) != NULL ) {
        if( strcmp(element->d_name, ".") == 0 ||  strcmp(element->d_name, "..") == 0)
            continue;

        lstat(element->d_name, &stbuf);

        printf("%s: ", element->d_name);

        if ( S_ISREG(stbuf.st_mode) ){
            puts("File");
        }
    }
*/

}