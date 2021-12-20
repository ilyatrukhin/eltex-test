#ifndef __TABLE_H__
#define __TABLE_H__

#include "global.h"

// минимальный вес ячейки
#define MIN_CELL_WEIGHT -1
// максимальный вес ячейки
#define MAX_CELL_WEIGHT 5

struct cell {
    int weight;         // вес ячейки
    void *player_ptr;   // указатель на игрока, занимающего поле, 
                                // чтобы в дальнейшем можно было обнулить его количество жизней
};

struct table{
    int size;
    struct cell **cells;
};

/* 
* Инициализация таблицы
* Параметры:
* size - размер таблицы
*/
struct table* init_table(int size);
/* 
* Освобождение ресурсов, выделенных для таблицы
* Параметры:
* tbl - указатель на таблицу
*/
void destroy_table(struct table *tbl);
/* 
* Проверка, занимает ли ячейку какой-либо игрок
* Параметры:
* tbl - указатель на таблицу
* coords - координаты ячейки
*/
void* is_cell_busy(struct table *tbl, struct point coords);
/* 
* Вывод таблицы на консоль
* Параметры:
* tbl - указатель на таблицу
*/
void print_table(struct table *tbl);

#endif