#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#define OK 0
#define ERR_EXIST_OF_FILE 1
#define ERR_TABLE 2
#define ERR_MEMORY 3
#define ERR_IN 4
#define SZ 31

struct data
{
    char type[10];
    char name[SZ];
    char gender[5];
    int age;
    float mark;
    int year;

    union
    {
        struct 
        {
            char address[SZ];
            int num_house;
            int num_flat;
        }house;
        
        struct 
        {
            int num_hostel;
            int num_room;
        }hostel;
        
    }condition;
};

struct data_table
{
    struct data *p;
    int sz;
    int n;
};

struct key
{
    int id;
    float value;
};

struct key_table
{
    struct key *p;
    int n;
};

void f_in_int(char *msg, int *num, int n);
void f_in_str(char *msg, char *str, int n);
void f_in_float(char *msg, float *num, int n);

void f_clear(struct data_table *d_t);
int f_add_to_table(struct data_table *d_t, struct data *d);
int f_load_table(char *str, struct data_table *d_t);
void f_show_data(struct data *d);
int f_show_data_table(struct data_table *d_t);
int f_save_data_table(char *str, struct data_table *d_t);
int f_input_data(struct data *p);
int f_check(char *str);
void f_remove(struct data_table *d_t, int num);
void f_clear_key_table(struct key_table *k_t);
int f_create_key_table(struct key_table *k_t, struct data_table *d_t);
int f_show_key_table(struct key_table *k_t);
void f_sort_insert_key(struct key_table *t_k);
void f_sort_table(struct data_table *t_k);
void f_show_sorted_key_table(struct data_table *d, struct key_table *k);
void f_sort_bubble_key(struct key_table *t_k);
void f_sort_table_bubble(struct data_table *t_k);
unsigned long long tick(void);
void f_search(struct data_table *p, int num);
#endif 