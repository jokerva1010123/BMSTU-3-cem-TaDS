#include "functions.h"

void f_in_str(char *msg, char *str, int n)
{
    for (;;)
    {
        printf("%s", msg);
        int i;
        char tmp;
        for (i = 0; ((tmp = getchar()) != '\n' && tmp != EOF && i < n); i++)
        {
            if (i == n)
                break;
            str[i] = tmp;
        }
        if (i == n)
        {
            printf("There are more than %d symbols\n\n", n - 1);
            continue;
        }
        if (i == 0)
        {
            printf("Empty input\n\n");
            continue;
        }
        str[i] = '\0';
        break;
    }
}

void f_in_int(char *msg, int *num, int n)
{
    char str[n];
    int i;
    for (;;)
    {
        f_in_str(msg, str, n);
        for (i = 0; str[i] != '\0'; i++)
            if (str[i] < '0' || str[i] > '9')
            {
                printf("Error input\n\n");
                i = 0;
                break;
            }
        if (i == 0)
            continue;
        *num = atoi(str);
        break;
    }
}

void f_in_float(char *msg, float *num, int n)
{
    char str[n];
    char c_str[n];
    int count, c_p = 0;
    float c_count = 1.0;
    unsigned int i; 
    for (;;)
    {
        f_in_str(msg, str, n);
        count = 0;
        for (i = 0; str[i] != '\0'; i++)
        {
            if ((str[i] < '0' || str[i] > '9') && (str[i] != '.' || count == 1))
            {
                printf("Error input\n\n");
                i = 0;
                break;
            }
            if (str[i] == '.')
            {
                count++;
                c_p = i + 1;
            }
        }
        if (i == 0)
            continue;
        count = 0;
        *num = atoi(str) / c_count;
        if (c_p != 0)
        {
            for (i = c_p; str[i] != '\0'; i++)
            {
                c_str[count] = str[i];
                count++;
                c_count *= 10;
            }
            *num += atoi(c_str) / c_count;
        }
        break;
    }
}

void f_clear(struct data_table *d_t)
{
    if(d_t->p)
        free(d_t->p);
    d_t->n = d_t->sz = 0;
}

int f_add_to_table(struct data_table *d_t, struct data *d)
{
    if(d_t->sz <= d_t->n)
    {
    //   /  struct data *p_f = d_t->p;
        struct data *tmp_p = d_t->p;
        d_t->sz += 10;
        struct data *ptr = (struct data *)malloc(sizeof(struct data) * d_t->sz);
        if(!ptr)
        {
            printf("The memory can not allocted\n");
            return ERR_MEMORY;
        }
        d_t->p = ptr;
        for(int i = 0; i < d_t->n; ++i)
        {
            *ptr = *tmp_p;
            ptr++;
            tmp_p++;
        }
    }
    d_t->p[d_t->n] = *d;
    d_t->n++;
    return OK;
}

int f_load_table(char *str, struct data_table *d_t)
{
    FILE *f = fopen(str, "r");
    if(!f)
    {
        printf("File does not exist\n");
        return ERR_EXIST_OF_FILE;
    }
    f_clear(d_t);
    int num, check = 1;
    int rc = fscanf(f, "%d", &num);
    if(rc != 1 || num < 1)
    {
        printf("Error in file\n");
        return ERR_TABLE;
    }
    fscanf(f, "\n");
    for(int i = 0; i < num; i++)
    {
        struct data *d = (struct data *)malloc(sizeof(struct data));
        if (!d)
        {
            printf("The memory can not allocated\n");
            return ERR_MEMORY;
        }
        if (fscanf(f, "%s\n", d->type) != 1)
            check = 0;
        char tmp[SZ];
        int k;
        fgets(tmp, 30, f);
        for(k = 0; tmp[k] != '\0'; k++);
        tmp[k-1] = tmp[k];
        strcpy(d->name, tmp);
        if (fscanf(f, "%s", d->gender) != 1)
            check = 0;
        if (fscanf(f, "%d", &d->age) != 1)
            check = 0;
        if (fscanf(f, "%f", &d->mark) != 1)
            check = 0;
        if (fscanf(f, "%d", &d->year) != 1)
            check = 0;
        if(strcmp(d->type, "house") && strcmp(d->type, "hostel"))
            check = 0;
        if(!strcmp(d->type, "house"))
        {
            fscanf(f, "\n");
            fgets(tmp, 30, f);
            for(k = 0; tmp[k] != '\0'; k++);
            tmp[k-1] = tmp[k];
            strcpy(d->condition.house.address, tmp);
            if(fscanf(f, "%d", &d->condition.house.num_house) != 1)
                check = 0;
            if(fscanf(f, "%d", &d->condition.house.num_flat) != 1)
                check = 0;
        }
        else
        {
            if(fscanf(f, "%d", &d->condition.hostel.num_hostel) != 1)
                check = 0;
            if(fscanf(f, "%d", &d->condition.hostel.num_room) != 1)
                check = 0;
        }
        if(!check)
        {
            fclose(f);
            printf("Error input\n");
            return ERR_TABLE;
        }        
        if (f_add_to_table(d_t, d))
        {
            fclose(f);
            return ERR_TABLE;
        }
        fscanf(f, "\n");
    }
    fclose(f);
    return OK;
}

void f_show_data(struct data *d)
{
    printf("|%-8s|", d->type);
    printf("%-15s|", d->name);
    printf("%-6s|", d->gender);
    printf("%-5d|", d->age);
    printf("%-8f|", d->mark);
    printf("%-8d|", d->year);
    if(!strcmp(d->type, "house"))
    {
        printf("%-15s|", d->condition.house.address);
        printf("%-8d|", d->condition.house.num_house);
        printf("%-7d|", d->condition.house.num_flat);
        printf("_________|");
        printf("_______|\n");
    }
    else
    {
        printf("_______________|");
        printf("________|");
        printf("_______|");
        printf("%-9d|", d->condition.hostel.num_hostel);
        printf("%-7d|\n", d->condition.hostel.num_room);
    }
}

int f_show_data_table(struct data_table *d_t)
{
    if(!d_t->n)
    {
        printf("Table is empty\n");
        return ERR_TABLE;
    }
    struct data *p = d_t->p;
    printf("|%-5s|", "Index");
    printf("%-8s|", "Type");
    printf("%-15s|", "Name");
    printf("%-6s|", "Gender");
    printf("%-5s|", "Age");
    printf("%-8s|", "Mark");
    printf("%-8s|", "Year");
    printf("%-15s|", "Address");
    printf("%-8s|", "No House");
    printf("%-7s|", "No Flat");
    printf("%-9s|", "No Hostel");
    printf("%-7s|\n", "No Room");
    for(int i = 0; i < d_t->n; i++)
    {
        printf("|%-5d", i+1);
        f_show_data(p);
        p ++;
    }
    return OK;
}   

int f_save_data_table(char *str, struct data_table *d_t)
{
    FILE *f = fopen(str, "w");
    if(!f)
    {
        printf("Can not open file");
        return ERR_EXIST_OF_FILE;
    }
    fprintf(f, "%d\n\n", d_t->n);
    struct data *p = d_t->p;
    for(int i = 0; i < d_t->n; i++)
    {
        fprintf(f, "%s\n", p->type);
        fprintf(f, "%s\n", p->name);
        fprintf(f, "%s\n", p->gender);
        fprintf(f, "%d\n", p->age);
        fprintf(f, "%f\n", p->mark);
        fprintf(f, "%d\n", p->year);
        if(!strcmp(p->type, "house"))
        {
            fprintf(f, "%s\n", p->condition.house.address);
            fprintf(f, "%d\n", p->condition.house.num_house);
            fprintf(f, "%d\n", p->condition.house.num_flat);
        }
        else
        {
            fprintf(f, "%d\n", p->condition.hostel.num_hostel);
            fprintf(f, "%d\n", p->condition.hostel.num_room);
        }
        fprintf(f, "\n");
        p++;
    }
    fclose(f);
    printf("Success\n");
    return OK;
}

int f_check(char *str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            printf("Number in string\n");
            return ERR_IN;
        }
        if(str[i] == ' ' && str[i + 1] !='\0' && ((str[i+1] > 'Z') || (str[i+1] < 'A')))
        {
            printf("After space must be uppercase\n");
            return ERR_IN;
        }
    }
    if((str[0] > 'Z') || (str[0] < 'A'))
    {
        printf("First letter must be uppercase\n");
        return ERR_IN;
    }
    return OK;
}

int f_input_data(struct data *p)
{
    printf("Input imformations of student:\n");
    char str[SZ];
    float f_num;
    f_in_str("house/hostel: ", str, SZ);
    if(!strcmp(str, "house"))
        strcpy(p->type, str);
    else if(!strcmp(str, "hostel"))
        strcpy(p->type, str);
    else
    {
        printf("Error input\n");
        return ERR_IN;
    }
    f_in_str("Name of student: ", str, SZ);
    if(f_check(str))
        return ERR_IN;
    strcpy(p->name, str);
    f_in_str("man/woman: ", str, SZ);
    if(!strcmp(str, "man"))
        strcpy(p->gender, "m");
    else if(!strcmp(str, "woman"))
        strcpy(p->gender, "w");
    else
    {
        printf("Error input\n");
        return ERR_IN;
    }
    f_in_int("Age of student: ", &p->age, SZ);
    if(p->age < 1 || p->age > 100)
    {
        printf("Error input1\n");
        return ERR_IN;
    }
    f_in_float("The score of student(from 2.0 to 5.0): ", &f_num, SZ);
    if(f_num >=2 && f_num <= 5)
        p->mark = f_num;
    else 
    {
        printf("Error input\n");
        return ERR_IN;
    }
    f_in_int("The year of admission: ", &p->year, SZ);
    if(p->year < 0)
    {
        printf("Error input\n");
        return ERR_IN;
    }
    if(!strcmp(p->type, "house"))
    {
        f_in_str("The street of house: ", str, SZ);
        if(f_check(str))
            return ERR_IN;
        strcpy(p->condition.house.address, str);
        f_in_int("The number of house: ", &p->condition.house.num_house, SZ);
        if(p->condition.house.num_house < 0)
        {
            printf("Error input\n");
            return ERR_IN;
        }
        f_in_int("The number of the flat: ", &p->condition.house.num_flat, SZ);
        if(p->condition.house.num_flat < 0)
        {
            printf("Error input\n");
            return ERR_IN;
        }
    }
    else
    {
        f_in_int("The number of hostel: ", &p->condition.hostel.num_hostel, SZ);
        if(p->condition.hostel.num_hostel < 0)
        {
            printf("Error input\n");
            return ERR_IN;
        }
        f_in_int("The number of the flat: ", &p->condition.hostel.num_room, SZ);
        if(p->condition.hostel.num_room < 0)
        {
            printf("Error input\n");
            return ERR_IN;
        }
    }
    return OK;
}

void f_remove(struct data_table *d_t, int num)
{
    struct data *p = d_t->p;
    for(int i = 0; i < d_t->n; i++)    
    {
        if(i >= num - 1)
            *p = *(p + 1);
        p++;
    }
    d_t->n --;
    p = NULL;
}

void f_clear_key_table(struct key_table *k_t)
{
    if(k_t->p)
    {
        free(k_t->p);
        k_t->p = NULL;
        k_t->n = 0;
    }
}

int f_create_key_table(struct key_table *k_t, struct data_table *d_t)
{
    struct data *p;
    struct key *k;
    f_clear_key_table(k_t);
    k_t->p = (struct key *)malloc(d_t->n*sizeof(struct key));
    if(!k_t->p)
    {
        printf("The memory can be allocated\n");
        return ERR_MEMORY;
    }
    k_t->n = d_t->n;
    k = k_t->p;
    p = d_t->p;
    for(int i = 0; i < d_t->n; i++)
    {
        k->id = i + 1;
        k->value = p->mark;
        k++;
        p++;
    }
    return OK;
}

int f_show_key_table(struct key_table *k_t)
{
    struct key *k = k_t->p;
    int count = k_t->n;
    if(!count)
    {
        printf("The key table is empty\n");
        return ERR_TABLE;
    }
    printf("|%-5s|%-10s|\n", "Index", "Value");
    for(int i = 0; i < count; i++)
    {
        printf("|%-5d|%-10f|\n", k->id, k->value);
        k++;
    }
    return OK;
}

void f_sort_insert_key(struct key_table *t_k)
{
    struct key *p = t_k->p;
    struct key tmp;

    int min;
    int n = t_k->n;

    for (int i = 0; i < n; i++)
    {
        min = i;

        for (int j = i; j < n; j++)
        {
            if (p[j].value < p[min].value)
                min = j;
        }
        tmp = p[i];
        p[i] = p[min];
        p[min] = tmp;
    }
}

void f_sort_table(struct data_table *t_k)
{
    struct data *p = t_k->p;
    struct data tmp;

    int min;
    int n = t_k->n;

    for (int i = 0; i < n; i++)
    {
        min = i;

        for (int j = i; j < n; j++)
        {
            if (p[j].mark < p[min].mark)
                min = j;
        }
        tmp = p[i];
        p[i] = p[min];
        p[min] = tmp;
    }
}

void f_show_sorted_key_table(struct data_table *d, struct key_table *k)
{
    struct data *ptr_d = d->p;
    struct key *ptr_k = k->p;
    printf("|%-5s", "Index");
    printf("|%-8s|", "Type");
    printf("%-15s|", "Name");
    printf("%-6s|", "Gender");
    printf("%-5s|", "Age");
    printf("%-8s|", "Mark");
    printf("%-8s|", "Year");
    printf("%-15s|", "Address");
    printf("%-8s|", "No House");
    printf("%-7s|", "No Flat");
    printf("%-9s|", "No Hostel");
    printf("%-7s|\n", "No Room");

    for (int i = 0; i < d->n; i++)
    {
        printf("|%-5d", i+1);
        f_show_data(&ptr_d[ptr_k[i].id - 1]);
    }
}

void f_sort_bubble_key(struct key_table *t_k)
{
    struct key *p = t_k->p;
    struct key tmp;

    int i = 0;
    int check = 1;

    while (check)
    {
        check = 0;

        for (int j = 0; j < t_k->n - i - 1; j++)
            if (p[j].value > p[j + 1].value)
            {
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
                check = 1;
            }

        i += 1;
    }
}

void f_sort_table_bubble(struct data_table *t_k)
{
    struct data *p = t_k->p;
    struct data tmp;

    int i = 0;
    int check = 1;

    while (check)
    {
        check = 0;

        for (int j = 0; j < t_k->n - i - 1; j++)
            if (p[j].mark > p[j + 1].mark)
            {
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
                check = 1;
            }

        i += 1;
    }
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void f_search(struct data_table *p, int num)
{
    struct data *ptr = p->p;
    int count = 0;

    printf("|%-8s|", "Type");
    printf("%-15s|", "Name");
    printf("%-6s|", "Gender");
    printf("%-5s|", "Age");
    printf("%-8s|", "Mark");
    printf("%-8s|", "Year");
    printf("%-15s|", "Address");
    printf("%-8s|", "No House");
    printf("%-7s|", "No Flat");
    printf("%-9s|", "No Hostel");
    printf("%-7s|\n", "No Room");

    for (int i = 0; i < p->n; i++)
    {
        if (num == ptr->year && !strcmp(ptr->type, "hostel"))
        {
            f_show_data(ptr);
            count++;
        }

        ptr++;
    }

    if (!count)
    {
        printf("|%-38s|\n"
               "|_____________________________________ |\n", \
               "There are not such students");
    }
}