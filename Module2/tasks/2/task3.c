// variant 6
/*
* Последовательность структурированных переменных типа 
* struct man { char name[20]; int  dd,mm,yy; char addr[]; }; 
* Последняя компонента представляет собой строку переменной размерности, 
* расположенную непосредственно за структурированной переменной. 
* Конец последовательности - структурированная переменная с пустой строкой в поле name.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define CHUNKSIZE 10
#define MAXNAMELEN 20

struct sdate{
    int dd, mm, yy;
};

struct man { 
    char name[MAXNAMELEN]; 
    struct sdate date; 
    char *addr; 
} man;

typedef struct people{
    int count;
    struct man *ppls;
} people;


void readData(people *);
void printData(people *);
void destroy(people *);

char *readString(FILE * );

/************** M A I N *************/
int main(int argc, char *argv[]){
    people *p = (people*)malloc(sizeof(people));
    readData(p);
    printData(p);
    destroy(p);
    return EXIT_SUCCESS;
}
/************************************/

char *readString(FILE *fp){
    char *line = NULL, *tmp = NULL;
    size_t size = 0, index = 0;
    int ch = EOF;

    while (ch) {
        ch = getc(fp);
        /* Check if we need to stop. */
        if (ch == EOF || ch == '\n')
            ch = 0;
        /* Check if we need to expand. */
        if (size <= index) {
            size += CHUNKSIZE;
            tmp = realloc(line, size);
            if (!tmp) {
                free(line);
                line = NULL;
                break;
            }
            line = tmp;
        }
        /* Actually store the thing. */
        line[index++] = ch;
    }
    return line;
}

void readData(people *p){
    char newline;
    printf("Укажите количество персон: ");
    scanf("%d", &p->count);
    scanf("%c", &newline);
    p->ppls = (struct man*)malloc(p->count * sizeof(struct man));
    printf("Для завершения введите пустую строку в поле name\n");
    for(int i = 0; i < p->count; ++i){
        p->ppls[i].name[sizeof(p->ppls[i].name) - 1] = '\0';
        printf("Name: ");
        if (fgets(p->ppls[i].name, MAXNAMELEN, stdin) == NULL) {
            p->count  = i;
            fprintf(stderr, "No more to read or IO error");
            break;
        }
        // если введенная строка оказалась больше доступной длины
        if(strlen(p->ppls[i].name) >= MAXNAMELEN - 2){
            if (p->ppls[i].name[sizeof(p->ppls[i].name) - 1] == '\0' && p->ppls[i].name[sizeof(p->ppls[i].name) - 2] != '\n') {
                int ch;
                while ((ch = fgetc(stdin)) != '\n' && ch != EOF);
            }
        }
        p->ppls[i].name[strlen(p->ppls[i].name) - 1] = '\0';

        if(*(p->ppls[i].name) != '\0' && *(p->ppls[i].name) != '\n'){            
            printf("Date in format dd mm yy: ");
            scanf("%d %d %d", &(p->ppls[i].date.dd), &(p->ppls[i].date.mm), &(p->ppls[i].date.yy));
            scanf("%c", &newline);
            printf("Address: ");
            p->ppls[i].addr = readString(stdin);
        }
        else{
            p->count = i;
            break;
        }
    }
}

void printData(people *p){
    printf("Количество персон: %d\n", p->count);
    printf("Name\t\tDate\t\tAddress\n");
    for(int i = 0; i < p->count; ++i){
        printf("%s\t\t%d.%d.%d\t\t%s\n", p->ppls[i].name, p->ppls[i].date.dd, p->ppls[i].date.mm, p->ppls[i].date.yy, p->ppls[i].addr);
    }
}

void destroy(people *p){
    for(int i = 0; i < p->count; ++i){
        free(p->ppls[i].addr);
        p->ppls[i].addr = NULL;
    }
    free(p->ppls);
    p->ppls = NULL;
    free(p);
    p = NULL;
}