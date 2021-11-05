#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#include "shm.h"

int main(int argc, char *argv[]){

    FILE *fp;
    char ch;
    if ((fp = fopen(PATHNAME, "r")) == NULL){
        fprintf(stderr, "Error of opening file\n");
        exit(1);
    }

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
        fclose(fp);
        fp = NULL;
        exit(1);
    }

    if((shmid = shmget(key, size*sizeof(char), SHMFLAGS|IPC_CREAT|IPC_EXCL)) < 0){
        if(errno != EEXIST){
            fprintf(stderr, "Can\'t create shared memory\n");
            fclose(fp);
            fp = NULL;
            exit(1);
        } 
        else {
            if((shmid = shmget(key, size*sizeof(char), 0)) < 0){
                fprintf(stderr, "Can\'t find shared memory\n");
                fclose(fp);
                fp = NULL;
                exit(1);
            }
        }
    }

    if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
        fprintf(stderr, "Can't attach shared memory\n");
        fclose(fp);
        fp = NULL;
        exit(1);
    }
    while ((ch = fgetc(fp)) != EOF){
        array[index++] = ch;
    }

    if(shmdt(array) < 0){
        fprintf(stderr, "Can't detach shared memory\n");
        fclose(fp);
        fp = NULL;
        exit(1);
    }

    fclose(fp);
    fp = NULL;

    return EXIT_SUCCESS;
}