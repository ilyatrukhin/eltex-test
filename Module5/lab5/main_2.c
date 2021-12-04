#include <stdio.h>
#include <stdlib.h>
#include ".env.h"

/* заголовочный файл для работы с динамическими библиотеками */
#include <dlfcn.h>

int main(int argc, char* argv[]){

	if(argc < 2){
		fprintf(stderr, "Usage: %s <function>\n", argv[0]);
		return EXIT_FAILURE;
	}

	void *ext_library;	// хандлер внешней библиотеки
	float value=0;		// значение для теста
	float (*func)(float x);	// переменные для хранения адресов функций
	//загрузка библиотеки
	ext_library = dlopen(PATH_TO_DYN_LIB, RTLD_LAZY);
	if (!ext_library){
		//если ошибка, то вывести ее на экран
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		return 1;
	};

	//загружаем из библиотеки требуемую процедуру
	func = dlsym(ext_library, argv[1]);
	if(func == NULL) {
		fprintf(stderr, "Function %s not found\n", argv[1]);
		return EXIT_FAILURE;
	}
	value=3.0;

	//выводим результат работы процедуры
	printf("%s(%f) = %f\n",argv[1],value,(*func)(value));

	//закрываем библиотеку
	dlclose(ext_library);
	return EXIT_SUCCESS;
}