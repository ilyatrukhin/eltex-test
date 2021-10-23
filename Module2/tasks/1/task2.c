// variant 7

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define CORRECT 1
#define INCORRECT 0

void extract( char *, size_t, size_t, size_t);
int extractAll( char *, size_t, char * );

int main(int argc, char *argv[]){
	
	if (argc < 2){
		fprintf(stderr, "Usage: %s <text>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char *buf = (char*)malloc(strlen(argv[1])*sizeof(char));
	char *res = (char*)malloc(strlen(argv[1])*sizeof(char));

	strcpy(buf, argv[1]);

	printf("Source:\n%s\n", buf);
	printf(" | \n");
	printf(" v \n");

	if(extractAll(buf, strlen(buf), res) == CORRECT){
		printf("Result:\n%s\n", res);
	}
	else{
		printf("В тексте пристуствуют непарные скобки или скобки заданы в неправильной последовательности\n");
	}

	free(buf);
	free(res);

	return EXIT_SUCCESS;
}

void extract( char *str, size_t len, size_t start, size_t end) {
	size_t shift = end - start + 1;
	for(int i = start; i < start + len - end; i++){
		str[i] = str[i + shift];
	}
	str[start + len - end] = '\0';
}

int extractAll( char *str, size_t len, char *res) {
	int curDepth;				// текущая глуюина погружения
	int maxDepth;				// максимальная глубина, достигнутая при прохождении всего текста
	size_t maxOpen = -1;		// индекс позиции левой скобки, соответствующей наиболее глубокой области
	size_t maxClose = len;		// индекс позиции правой скобки, соответствующей наиболее глубокой области
	int isClosed;				// флаг, определяющий, была ли закрыта исследуемая область правой скобкой
	size_t curStrLength = len;	// текущая длина исследуемого текста
	int curResLength = 0;		// текущая длина результата с извлеченными частями текста
	int status;

	do {
		curDepth = 0;
		maxDepth = 0;
		isClosed = 1;
		maxOpen = -1;
		maxClose = curStrLength;
		status = CORRECT;

		for(size_t i = 0; i < curStrLength; i++){
			if(str[i] == '{') {
				curDepth++;
				if (curDepth > maxDepth){
					isClosed = 0;
					maxDepth = curDepth;
					maxOpen = i;
				}
			}
			if(str[i] == '}') {
				curDepth--;
				if(curDepth < 0){
					status = INCORRECT;
					return status;
				}
				if(!isClosed){
					maxClose = i;
					isClosed = 1;
				}
			}
		}
		if (curDepth > 0) {
			status = INCORRECT;
			return status; 
		}

		if (status == CORRECT){
			for(int i = maxOpen + 1; i < maxClose; i++){
				res[curResLength++] = str[i];
			}
			res[curResLength] = '\0';
			extract(str, curStrLength, maxOpen, maxClose); 
			curStrLength -= (maxClose - maxOpen + 1);
		}
	} while (maxOpen != -1 && maxClose != curStrLength);
	return status;
}