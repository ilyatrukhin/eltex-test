#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgq.h"

int main(int argc, char *argv[]){
    msgbuf sdmsg, rcmsg;
    int msqid;
    key_t key; 
    int len = sizeof(pid_t); 
    int maxlen = len;
    pid_t pid = getpid();
    sdmsg.mtype = SERVERMTYPE;
    sdmsg.pid = pid;
    printf("Process %d sent message\n", sdmsg.pid);


    if((key = ftok(PATHNAME,0)) < 0){
        printf("Can\'t generate key\n");
        exit(1);
    }

    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(1);
    }

    if (msgsnd(msqid, (struct msgbuf *) &sdmsg, len, 0) < 0){
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(1);
    }

    if((len = msgrcv(msqid, (struct msgbuf *) &rcmsg, maxlen, pid, 0)) < 0){
        printf("Can\'t receive message from queue\n");
        exit(1);
    }

    printf("Answer from server: mtype = %ld, pid = %d\n", rcmsg.mtype, rcmsg.pid);

    return EXIT_SUCCESS;
}