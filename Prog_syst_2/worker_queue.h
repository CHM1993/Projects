/* 
 * File:   worker_queue.h
 * Author: adminuser
 *
 * Created on April 20, 2015, 9:44 AM
 */

#ifndef WORKER_QUEUE_H
#define	WORKER_QUEUE_H

#include <stdbool.h>


typedef struct worker{

struct worker *head;
struct worker *tail;
bool status;
int worker_id;
pid_t pid;
char worker_line[30];		     
}worker;


pid_t run_worker(char* message);
int entry_worker(int status,int job_id,worker** head_running,worker** head_waiting,worker** tail,char* worker_line);
int update_pid(pid_t pid,worker* tail);
pid_t stop_worker(worker** head_waiting,worker** head_running,worker** tail,int jobid,pid_t pid);
char* get_worker(worker** head_waiting);
#endif	/* WORKER_QUEUE_H */



