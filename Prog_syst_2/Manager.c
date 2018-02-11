#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "worker_queue.h"

/*GLOBAL */

int request=0;
int running=0;
int alarmed=0;



/*ADeios! Xriazete mono gia na apenergopiei tin pause() */

void AlarmHandler()
{
printf("ALARMED!\n");
alarmed++;
}

void FileHandler()
{
printf("\nlistener:Got shot!\n");
request++;
}


void ChildHandler()
{
running--;
}

void my_handler(int s){
   printf("Caught signal %d\n",s);
   exit(1); 

}


int main(int argc,char** argv){
    int fd,fdp,i;
    char cwd[1024];
    char pid_c[11]={0},keno=' ';
    pid_t listener_id;
    ssize_t chars;
    char *ptr;
    char *new=NULL;
    int N=3,waiting=0, status=200;
    worker *head_running=NULL,*head_waiting=NULL,*tail=NULL,*temp=NULL;
    pid_t jpid;
    char message[30];
    int worker_id = 1;

    /*gia na elenxw an yparxei o listener dimiourgw ena arxeio ,an yparxei simainei oti yparxei kai o listener*/
    struct sigaction sigIntHandler;

   sigIntHandler.sa_handler = my_handler;
   sigemptyset(&sigIntHandler.sa_mask);
   sigIntHandler.sa_flags = 0;
        
    listener_id = fork();

    if( listener_id == 0){       /*Ekkinisi Listener */
        char* argvf[]={"listener", NULL};
        execv("Listener",argvf);
    }
    
    fd=open("listener_pipe",O_RDWR |O_CREAT | O_EXCL,0660);


    /* Egatastasi twn signal handlers */

    signal(SIGALRM,AlarmHandler);
    signal(SIGUSR1,FileHandler);
    signal(SIGCHLD,ChildHandler);

    
    while(1){
        
        while(!request && (running>=N || waiting<=0) )
	{
 
            alarm(30);                                               /*Alarm se periptwsi pou xathike to sima anamesa sto while kai to pause*/
            printf("\no listener perimenei...%d paramenoun mexri na klisei aytomata\n",alarmed*30);

            pause();




            if(alarmed==2)          /*An dn erthei sima o job executor termatizei meta apo 60 deuterolepta*/
            {
            unlink("listener_pipe");                 /*klisimo pipe kai arxeio me tin PID tou Job executor*/
             printf("EXIT FROM WAITING AT PAUSE() CALL!/n");
            exit(1);
            }


            alarm(0);
	}
        
    
        alarmed=0;


        /*DEXRIKA SIMA*/




        /* Katharismos zombie diergasiwn */

        while((jpid=waitpid(-1,&status,WNOHANG))>0 ){
            i = stop_worker(&head_waiting,&head_running,&tail,-1,jpid);
        }




        /*Ektelisi job pou perimenoun stin oura enw molis dimiourgithike xwros */
        printf("\n\nrunning %d waiting %d\n\n",running,waiting);
        
        if( running<N && waiting>0 )
        {
            temp=head_waiting;
            new=get_worker(&head_waiting);
            waiting--;
            running++;
            jpid=run_worker(new);
            update_pid(jpid,temp);
        }
        
        if(request){

/*Diavasma tis entolis apo to pipe*/





            i=0;

            while( read(fdp,&(message[i]),1))
            {
                i++;
            }
            /*diavase olo to minima*/
            
            request--;
            /*paw na dimiourgisw worker*/
            if( waiting==0){

		  entry_worker(1,worker_id,&head_running,&head_waiting,&tail,&(message[strlen(message)+1]));
		  jpid=run_worker(&(message[strlen(message)+1]));
		  update_pid(jpid,tail);
		  running++;

            }
            else{

              entry_worker(0,worker_id,&head_running,&head_waiting,&tail,&(message[strlen(message)+1]));
              waiting++;

            }
		
            worker_id = worker_id + 1;
            
            if( sigaction(SIGINT, &sigIntHandler, NULL)){  /*PREPEI NA TERMATISTOUN OLOI OI WORKERS KAI TO PROGRAMMA*/
                if(tail==NULL) {
                    printf("No workers!/n");
                    continue;
		}
                else{
                    while (tail != NULL){ /*svinw olous tous workers*/
                        
                        jpid=stop_worker(&head_waiting,&head_running,&tail,i,0);
	
                        if(jpid!=-30)
                        {
                            printf("killing procces %d\n",jpid,0);
                            kill(jpid,SIGKILL);
                        }
                        else{
                            waiting--;
                        }
                        
                    }
                    printf("now we exit program\n");
                    unlink("listener_pipe");   
                    exit(0);
                }
            }
        }
    }
}
