#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "global.h"

// количество возможных направлений движения игрока
#define COUNT_OF_DIRECTIONS 4
// длина шага вдоль оси OX
#define STEP_LENGTH_OX 1
// длина шага вдоль оси OY
#define STEP_LENGTH_OY 1
// индикатор выхода за границу карты
#define OUT_OF_RANGE -1

// возможно, будет использовано в дальнейшей разработке,
// когда игрокам нужно будет задать роли
#if 0
enum role {
    ORDINARY,
    EXTRA
};
#endif

// направления движения
enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// базоввая информация об игроке
struct player_info{
    int id;
};

struct player{
#if 0
    enum role role;
#endif
    enum direction direction;
    struct player_info info;
    int count_lifes;
    struct point position;
    void (*move)(struct player *p);
};

/* 
* Инициализация игрока
* Параметры:
* number - порядковый номер игрока
* id - идентификатор игрока
*/
struct player* init_player(int number, int id);
/* 
* Освобождение выделенных ресурсов для игрока
* Параметры:
* p - указатель на игрока
*/
void destroy_player(struct player *p);

/* 
* Передвижение игрока
* Параметры:
* p - порядковый номер игрока
*/
void move_player(struct player *p);

/* 
* Задать координаты игрока
* Параметры:
* p - указатель на игрока
* coords - координаты
*/
void set_player_position(struct player *p, struct point coords);
/* 
* Сражение игроков, в результате которого у одного
* обнуляется кол-во жизней, при этом игрок-победитель не получает ничего
* (разве что возможность пожить подольше ...)
* Параметры:
* p1, p2 - указатели на игроков игрока
*/
void battle(struct player *p1, struct player *p2);
/* 
* Убить игрока (обнулить жизни)
* Параметры:
* p - указатель на игрока
*/
void kill_player(struct player *p);
/* 
* Проверка, жив ли игрок 
* Параметры:
* p - указатель игрока
*/
int is_player_alive(struct player *p);
/* 
* Вывод информации "от имени" игрока p
* Параметры:
* p - указатель на игрока
* msg - текст сообщения, которое игрок p должен вывести от своего имени
*/
void player_log(struct player *p, const char *msg);

#endif