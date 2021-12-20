#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <malloc.h>
#include <unistd.h>

#include "game.h"

// параметры функции потока
struct thread_arg {
    int number;
    struct table *table;
    pthread_mutex_t *mutex;
};

// ввод цолочисленного параметра
int get_int_param(const char *);
// фукнция потока
void *player_thread(void *);

void err();


/******************** MAIN ********************/
int main(int argc, char *argv[]){

    int thread_count = 0;
    int table_size = 0;

    if(argc < 3){
        thread_count = get_int_param("Set thread count");
        table_size = get_int_param("Set table size");
    }
    else{
        thread_count = atoi(argv[1]);
        table_size = atoi(argv[2]);
        if(thread_count <= 0){
            err("Incorrect thread count!");
        }
        if(table_size <= 0){
            err("Incorrect table size!");
        }
    }

    srand(getpid());
    pthread_t *threads;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    threads = (pthread_t*)malloc(sizeof(pthread_t) * thread_count);
    if(!threads){
        err(EMALLOC_MSG);
    }

    struct table *tbl = init_table(table_size);

    fprintf(stdout, "Game starting ...\n");
    fprintf(stdout, "Thread count: %d\n", thread_count);

    print_table(tbl);
    for(int i = 0; i < thread_count; ++i){
        struct thread_arg *arg = (struct thread_arg *)malloc(sizeof(struct thread_arg));
        arg->mutex = &mutex;
        arg->table = tbl;
        arg->number = i;
        pthread_create(&threads[i], NULL, player_thread, arg);
    }

    for(int i = 0; i < thread_count; ++i){
        pthread_join(threads[i], NULL);
    }

    fprintf(stdout, "Game over\n");

    free(threads);
    threads = NULL;

    return EXIT_SUCCESS;
}

/****************** END MAIN ******************/

void *player_thread(void *arg){
    int number = ((struct thread_arg*)arg)->number;
    struct table *table = ((struct thread_arg*)arg)->table;
    struct player *p = init_player(number, number);
    pthread_mutex_t *mutex = ((struct thread_arg*)arg)->mutex;

    int x = rand() % table->size;
    int y = rand() % table->size;

    set_player_position(p, (struct point) {x, y});

    fprintf(stdout, "Player #%d took position (%d; %d)\n", number, x, y);

    while(is_player_alive(p)){
        pthread_mutex_lock(mutex);
        make_step(table, p);
        pthread_mutex_unlock(mutex);
        sleep(2);
    }
    destroy_player(p); 
    free(arg);
    arg = NULL;
    fprintf(stdout, "Exit from thread #%d\n", number);
    pthread_exit(NULL);
}

int get_int_param(const char *msg){
    int param;
    fprintf(stdout, "%s: ", msg);
    fscanf(stdin, "%d", &param);
    if(param <= 0){
        err("Incorrect value!");
    }
    return param;
}

void err(const char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}