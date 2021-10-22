// variant 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int isPalind(char*, size_t);
void delMaxPalindAndSpaces(char*, char*, size_t);
char *getEndOfWord(const char *);
char *getStartOfNextWord(const char *);
int isDelimiter(const int);

/************** M A I N **************/
int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *buf = (char*)malloc(strlen(argv[1])*sizeof(char));
    char *res = (char*)malloc(strlen(argv[1])*sizeof(char));
    strcpy(buf, argv[1]);
    printf("%s\n", buf);
    delMaxPalindAndSpaces(buf, res, strlen(buf));
    printf("Result:\n%s\n", res);
    
    free(buf);
    free(res);
    return EXIT_SUCCESS;
}
/*************************************/

int isPalind(char *str, size_t len){
    if (len < 2) return 0;
    for(size_t i = 0; i < len / 2; i++){
        if (str[i] != str[len - i - 1])
            return 0;
    }
    return 1;
}


void delMaxPalindAndSpaces(char *src, char *res, size_t len){
    char *start, *end, *startMax, *endMax;
    memset(res, 0, len);
    start = src;
    startMax=  start;
    endMax = start;
    int curLen = 0;
    while (start != NULL){
        end = getEndOfWord(start);
        if(isPalind(start, end - start)){ 
			if (end - start > endMax - startMax){
					startMax = start;
					endMax = end;
			}
        } 
        start = getStartOfNextWord(end);
    }
    
    for(char *p = src; p != startMax; ++p)
		if(*p != ' ')
			res[curLen++] = *p;
        
    for(char *p = endMax; p != end; ++p)
		if(*p != ' ')
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
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0' || ch == ',' || ch == ';' || ch == ':' || ch == '?' || ch == '!';
}
