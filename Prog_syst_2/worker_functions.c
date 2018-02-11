
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include "worker_queue.h"




pid_t run_worker(char* message)
{

   /*tha anoixw to arxeio pou vriskete sto message kai tha t diavasw*/

    FILE *fp;
    FILE *fp2;
    char ch;
    char buff[1000],sub1[1000],sub2[1000], outfile[1000];
    int i=0;
    int j=0;
    pid_t pid;
    
    fp = fopen(message,"r"); // read mode
 
       if( fp == NULL )
       {
          perror("Error while opening the file.\n");
          exit(EXIT_FAILURE);
       }
    
       i = 0;
       while( ( ch = fgetc(fp) ) != EOF ){
          printf("%c",ch);
          if ((ch == 'h') &&(i == 0)){
              buff[i] = ch;
              i++;
          }
          if ((ch == 't') &&((i == 1) || (i == 2))){
              buff[i] = ch;
              i++;
          }
          if ((ch == 'p') &&(i == 3)){
              buff[i] = ch;
              i++;
          }
          else{
              i = 0;
              strcpy(buff, NULL);
          }
          if(strcmp(buff,"http") == 0){ /*pame na vroume to domain*/
              while( ( ch = fgetc(fp) ) != '/' ){
                  buff[i] = ch;
                  i++;
              }
              buff[i] = '/';
              j = 0;
              while(buff[j] != '/'){
                while (buff[j] != '.'){

                    sub1[j] = buff[j];
                    j++;
                }
                j++;
                while (buff[j] != '.'){

                    sub2[j] = buff[j];
                    j++;
                }
              }
              strcpy(outfile, message);
              strcat(outfile,".out");
              fp2 = fopen(outfile, "w");
              fputs(sub1, fp);
              fputs(sub2, fp);
          }
          
       }
       fclose(fp);
       
       /*EKINISI DIERGASIAS*/
       pid = fork();
       return pid;

}





int entry_worker(int status,int job_id,worker** head_running,worker** head_waiting,worker** tail,char* worker_line)
{
worker* temp;

temp= (worker*)malloc( sizeof(worker));

if(temp==NULL)
return 1;



temp->status=status;
temp->worker_id=job_id;
temp->head=*tail;
temp->tail=NULL;
strcpy(temp->worker_line,worker_line);

temp->pid=-10;



if(*tail==NULL)
{
        /*an einai o prwtos komvos pou eisagete tote einai tautoxrona prwtos kai teleutaios tis ouras*/

if(!status)
*head_waiting=temp;
else
*head_running=temp;

}
else 
{

(*tail)->tail=temp;

if( (*tail)->status  &&  !(temp->status) )          /*An o proigoumenos worker einai running(ektelite) tote eimai o prwtos pou perimenei*/
*head_waiting=temp;

}






*tail=temp;             /*O kainourgios komvos ginete o teleutaios komvos tis ouras*/


printf("status %d pid %d job_id %d head_running %p head_waiting %p tail %p job: %s \n", temp->status,temp->pid,temp->worker_id,*head_running,*head_waiting,*tail,temp->worker_line);


return 0;

}

int update_pid(pid_t pid,worker* tail){
    tail->pid=pid;
}

pid_t stop_worker(worker** head_waiting,worker** head_running,worker** tail,int jobid,pid_t pid)
{
worker* temp;

/*ksekinw apo to telos gia na psaksw ton komvo*/

temp=*tail;

if( jobid != -1)
{

while( temp!=NULL && temp->worker_id!=jobid)
temp=temp->head;


}
else
{

while( temp!=NULL && temp->pid!=pid)
temp=temp->head;



}




if(temp==NULL)
{printf("This workerID does not exist or is already deleted from que\n");
return 0;
}




if(temp->head==NULL)         /*An vgazoume ton prwto komvo*/
{



	



	
	if(temp->tail==NULL)
	{

	 *tail=NULL;
		if(temp->status)
	{
		*head_running=NULL;

	}
		else
		*head_waiting=NULL;
	}
	else if( temp->status )       /*An o prwtos einai running*/
	{
		if( (temp->tail)->status )             /*An o proigoumenos komvos einai running(status:1) */
		*head_running=temp->tail;	       /*ginete o kainourgios prwtos komvos running kai prwtos komvos tis ouras*/
		else
		*head_running=NULL;

	 (temp->tail)->head=NULL;                   /*kainourgios prwtos komvos tis ouras */

	}
	else                      /*An o prwtos komvos einai waiting(status:0) sigoura oloi osoi einai pisw apo auton einai waiting*/
	{
	 (temp->tail)->head=NULL;
	 *head_waiting=temp->tail;
	}



}else if(temp->tail==NULL)        /*an vgazoume ton teleutaio komvo*/
{
	*tail= temp->head;
	(temp->head)->tail=NULL;

	if( !(temp->status) )
	{
		if( (temp->head)->status )
		*head_waiting=NULL;


	}


}
else     /* O komvos pou afairoume einai anamesa se allous komvous*/
{
	(temp->head)->tail=temp->tail;
	(temp->tail)->head=temp->head;
	
	if( !temp->status )
	{
		if( (temp->head)->status )     /*an o epomenos komvos einai running eimai ston head_waiting ara o proigoumenos */
		*head_waiting=temp->tail;      /* komvos  ginete o kainourgios head_waiting */
	}


}

if( temp->status )
return temp->pid;
else 
return -30;

free(temp);

}

char* get_worker(worker** head_waiting)
{
    worker* temp;

    temp=*head_waiting;

    temp->status=1;

    *head_waiting=temp->tail;

    return temp->worker_line;

}