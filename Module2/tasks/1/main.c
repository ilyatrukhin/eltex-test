#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

void invStr(char*, size_t);
void invWordsInText(char *);
int isPalind(char*, size_t);
void delPalind(char*, char*, size_t);
char *getEndOfWord(const char *);
char *getStartOfNextWord(const char *);
int isDelimiter(const int);

/************** M A I N **************/
int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *buf = (char*)malloc(strlen(argv[1])*sizeof(char));
    char *res = (char*)malloc(strlen(argv[1])*sizeof(char));
    strcpy(buf, argv[1]);
    invWordsInSentence(buf);
    printf("%s %ld\n", buf, strlen(buf));
    delPalind(buf, res, strlen(buf));
    printf("%s\n", res);
    
    free(buf);
    free(res);
    return EXIT_SUCCESS;
}
/*************************************/

void invStr(char *str, size_t len){
    char tmp;
    for(size_t i = 0; i < len / 2; i++){
        tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

void invWordsInText(char *str){
    char *start, *end;
    start = str;
    while (start != NULL){
        end = getEndOfWord(start);
        invStr(start, end - start);
        start = getStartOfNextWord(end);
    }
}


int isPalind(char *str, size_t len){
    if (len < 2) return 0;
    for(size_t i = 0; i < len / 2; i++){
        if (str[i] != str[len - i - 1])
            return 0;
    }
    return 1;
}


void delPalind(char *src, char *res, size_t len){
   
    char *start, *end;
    char *ptr;
    memset(res, 0, len);
    start = src;
    ptr = start;
    int curLen = 0;
    while (start != NULL){
        end = getEndOfWord(start);
        if(isPalind(start, end - start)){ 
            for(char *p = ptr; p != start; ++p)
                res[curLen++] = *p;      
            ptr = end;
        } 
        start = getStartOfNextWord(end);
    }
    
    for(char *p = ptr; p != end; ++p)
        res[curLen++] = *p;
}


char *getEndOfWord(const char *p) {
    for (;; ++p) {
		if (isDelimiter(*p))
			return ((char *)p);
		if (*p == '\0')
			return (NULL);
	}
}

char *getStartOfNextWord(const char *p) {
    for (;; ++p) {
		if (!isDelimiter(*p))
			return ((char *)p);
		if (*p == '\0')
			return (NULL);
	}
}

int isDelimiter(int ch){
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0';
}
