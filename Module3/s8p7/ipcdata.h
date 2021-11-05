#ifndef __IPCDATA_H__
#define __IPCDATA_H__

#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PATHNAME "prog1.c"
#define SHMFLAGS 0666
#define SEMFLAGS 0666

union semun {
    int val;                  /* значение для SETVAL */
    struct semid_ds *buf;     /* буферы для  IPC_STAT, IPC_SET */
    unsigned short *array;    /* массивы для GETALL, SETALL */
                           /* часть, особенная для Linux: */
    struct seminfo *__buf;    /* буфер для IPC_INFO */
};

#endif