#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgq.h"
#include "thpool.h"

int msqid; 

void task(void *arg) {
    pid_t pid = (intptr_t) arg;
    //printf("Thread #%u working on %d\n", (int)pthread_self(), pid);
    msgbuf sdmsg = {(int)pid, 0};
    int len = sizeof(pid_t);

    // имитация долгой обработки сообщения
    for (long i = 0; i < 1000000000; ++i);

    if (msgsnd(msqid, (struct msgbuf *) &sdmsg, len, 0) < 0){
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(1);
    }
}

int main(int argc, char *argv[]){

    key_t key; 
    int len, maxlen = sizeof(pid_t); 

    msgbuf rcmsg;

    if((key = ftok(PATHNAME,0)) < 0){
        printf("Can\'t generate key\n");
        exit(1);
    }

    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(1);
    }

	threadpool thpool = thpool_init(4);

    while(1){

        if((len = msgrcv(msqid, (struct msgbuf *) &rcmsg, maxlen, SERVERMTYPE, 0)) < 0){
            printf("Can\'t receive message from queue\n");
            exit(1);
        }

        printf("message type = %ld, pid = %d\n", rcmsg.mtype, rcmsg.pid);
        thpool_add_work(thpool, task, (void*)(intptr_t)rcmsg.pid);
    }
	
	//thpool_wait(thpool);
	//puts("Killing threadpool");
	//thpool_destroy(thpool);
    return EXIT_SUCCESS;
}