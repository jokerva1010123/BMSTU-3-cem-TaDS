#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include "general.h"

#define MAX_STACK_SIZE 100  //Максимальный размер стека

// реализация стека в виде массива
typedef struct
{
    char data[MAX_STACK_SIZE];  //элементы стека
    int cur_size;               // текущий размер стека
} arr_stack_t;

// реализация стека в виде списка
typedef struct list_stack
{
    int value;                      // значение элемента
    int index;                      // индекс элемента
    struct list_stack *prev;        // указатель на предыдущий элемент стека
} list_stack_t;


// массив свободных областей
typedef struct
{
    size_t *arr;            // массив адресов
    int len;                // текущее число адресов
} free_areas_t;

#endif