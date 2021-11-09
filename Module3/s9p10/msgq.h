#ifndef __MSGQ_H__
#define __MSGQ_H__

#define PATHNAME "msgq.h"
#define SERVERMTYPE 1

typedef struct msgbuf{
    long mtype;
    pid_t pid;
} msgbuf;

#endif