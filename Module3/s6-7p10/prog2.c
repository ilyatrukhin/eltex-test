#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#include "shm.h"

int main(int argc, char *argv[]){

    struct stat st;
    stat(PATHNAME, &st);
    size_t size = st.st_size;
    printf("Size %ld\n", size);

    char *array; /* Указатель на разделяемую память */
    int shmid; /* IPC дескриптор для области разделяемой памяти */
    key_t key; /* IPC ключ */
    int index = 0;

    if((key = ftok(PATHNAME, 0)) < 0){
        fprintf(stderr, "Can\'t generate key\n");
        return EXIT_FAILURE;
    }

    if((shmid = shmget(key, size*sizeof(char), SHMFLAGS|IPC_CREAT|IPC_EXCL)) < 0){
        if(errno != EEXIST){
            fprintf(stderr, "Can\'t create shared memory\n");
            return EXIT_FAILURE;
        } 
        else {
            if((shmid = shmget(key, size*sizeof(char), 0)) < 0){
                fprintf(stderr, "Can\'t find shared memory\n");
                return EXIT_FAILURE;
            }
        }
    }

    if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
        fprintf(stderr, "Can't attach shared memory\n");
        return EXIT_FAILURE;
    }

    while (index < size){
        printf("%c", array[index++]);
    }

    if(shmdt(array) < 0){
        fprintf(stderr, "Can't detach shared memory\n");
        return EXIT_FAILURE;
    }
    if(shmctl(shmid, IPC_RMID, NULL) < 0){
        fprintf(stderr, "Can't remove segment of shared memory\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}