#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
#include "ipcdata.h"

int main(int argc, char *argv[])
{
    key_t key;
    int semid;
    union semun arg;
    
    if ((key = ftok(PATHNAME, 0)) == -1){
        perror("ftok");
        exit(1); 
    }
    
    /* create a semaphore set with 1 semaphore: */
    if ((semid = semget(key, 1, SEMFLAGS | IPC_CREAT)) == -1){
        perror("semget");
        exit(1); 
    }
    /* initialize semaphore #0 to 1: */ arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1){
        perror("semctl");
        exit(1); 
    }
    return 0; 
    
}