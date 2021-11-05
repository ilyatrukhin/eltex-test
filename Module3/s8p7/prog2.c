#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "ipcdata.h"

int main(int argc, char *argv[]){
    int *array;
    int shmid;
    int semid;
    int new = 1;
    key_t key;
    long i;

    struct sembuf lock_res = {0, -1, 0};	//блокировка ресурса
	struct sembuf rel_res = {0, 1, 0};	//освобождение ресурса

    if((key = ftok(PATHNAME, 0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if((shmid = shmget(key, 3*sizeof(int), SHMFLAGS|IPC_CREAT|IPC_EXCL)) < 0){
        if(errno != EEXIST){
            printf("Can\'t create shared memory\n");
            exit(-1);
        }
        else {
            if((shmid = shmget(key, 3*sizeof(int), 0)) < 0){
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
            new = 0;
        }
    }

    if((semid = semget(key, 1, SEMFLAGS | IPC_CREAT)) < 0){
        printf("Can\'t get semid\n");
        exit(-1);
    }

    if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    if((semop(semid, &lock_res, 1)) == -1){
        fprintf(stderr, "Lock failed\n");
        exit(1);
    }
    printf("Inside critical section\n");
    // КРИТИЧЕСКАЯ СЕКЦИЯ
    if(new){
        array[0] = 0;
        array[1] = 1;
        array[2] = 1;
    }
    else {
        array[1] += 1;

        for(i=0; i<1000000000L; i++);
        array[2] += 1;
    }
    // КОНЕЦ КРИТИЧЕСКОЙ СЕКЦИИ
    if((semop(semid, &rel_res, 1)) == -1){
        fprintf(stderr, "Unlock failed\n");
        exit(1);
    }

    printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
    array[0], array[1], array[2]);

    if(shmdt(array) < 0){
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    return 0;
}