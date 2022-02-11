#include "functions.h"

struct data_table d_t = {NULL, 0, 0};
struct key_table k_t = {NULL, 0};

int main(void)
{
    int num;
    char str[SZ];
    int check = 0;

    while(1)
    {
        printf("Menu:\n\n"
                "1 - Load table\n"
                "2 - Show table\n"
                "3 - Save table\n"
                "4 - Add to table\n"
                "5 - Remove from table\n"
                "6 - Creat key table\n"
                "7 - Show key table\n"
                "8 - Sort key table\n"
                "9 - Sort table\n"
                "10 - Show sort table by key key table\n"
                "11 - Search in table\n"
                "12 - Show program effective\n"
                "0 - Exit\n\n");
        f_in_int("Input number: ", &num, SZ);
        switch (num)
        {
            case 1:
            {
                f_in_str("Input name of file: ", str, SZ);
                if(f_load_table(str, &d_t))
                    continue;
                printf("Success\n");
                break;
            }
            case 2:
            {
                if(f_show_data_table(&d_t))
                    continue;
                break;
            }
            case 3:
            {
                f_in_str("Input name of file: ", str, SZ);
                if(f_save_data_table(str, &d_t))
                    continue;
                break;
            }
            case 4:
            {
                struct data d_a;
                if(f_input_data(&d_a))
                    continue;
                if(f_add_to_table(&d_t, &d_a))
                    continue;
                printf("Success\n");
                break;
            }
            case 5:
            {
                if(!d_t.n)
                {
                    printf("The table is empty\n");
                    continue;
                }
                printf("Input index of the element(From 1 to %d): \n", d_t.n);
                f_in_int("Index: ", &num, SZ);
                if(num < 1 || num > d_t.n)
                {
                    printf("The index must be in range from 1 to %d\n", d_t.n);
                    continue;
                }
                f_remove(&d_t, num);
                printf("Success\n");
                break;
            }
            case 6:
            {
                if(!d_t.n)
                {
                    printf("The table is empty\n");
                    continue;
                }
                if(f_create_key_table(&k_t, &d_t))
                    continue;
                printf("Success\n");
                break;
            }
            case 7:
            {
                if(!k_t.n)
                {
                    printf("Error key table\n");
                    continue;
                }
                if(f_show_key_table(&k_t))
                    continue;
                break;
            }
            case 8:
            {
                if (k_t.n == 0)
                {
                    printf("Error key table\n");
                    continue;
                }
                f_sort_insert_key(&k_t);
                printf("The key table is sorted successfully\n");
                break;
            }
            case 9 :
            {
                if (d_t.n == 0)
                {
                    printf("The table of data is empty\n");
                    continue;
                }

                f_sort_table(&d_t);

                check = 1;

                printf("The data table is sorted successfully\n");

                break;
            }
            case 10 :
            {
                if (d_t.n == 0 || k_t.n == 0)
                {
                    printf("The table of data or key table are empty\n");
                    continue;
                }

                if (check)
                {
                    printf("The data table is already sorted\n");
                    continue;
                }

                f_show_sorted_key_table(&d_t, &k_t);

                break;
            }
            case 11 :
            {
                if (d_t.n == 0)
                {
                    printf("The table of data is empty\n");
                    continue;
                }
                f_in_int("Input the year of admission: ", &num, SZ);
                f_search(&d_t, num);

                break;
            }
            case 12 :
            {
                f_in_str("Input the name of the file: "
                        "\n|______________________________| 30 symbols\n|", \
                        str, SZ);

                struct data_table d_t1 = { NULL, 0, 0 };
                struct data_table d_t2 = { NULL, 0, 0 };
                struct key_table t_k1 = { NULL, 0 };
                struct key_table t_k2 = { NULL, 0 };

                if (f_load_table(str, &d_t1))
                    continue;

                if (f_load_table(str, &d_t2))
                    continue;

                printf("The table is loaded successfully\n");

                if (d_t1.n == 0)
                {
                    printf("The table of data is empty\n");
                    continue;
                }

                if(f_create_key_table(&t_k1, &d_t1))
                    continue;

                if(f_create_key_table(&t_k2, &d_t2))
                    continue;

                printf("The table of key is created successfully\n");
                printf("The key table is sorted successfully\n");
                printf("The data table is sorted successfully\n\n");
                printf("|%-15s|%-10s|%-10s|\n", "", "Data table", "Key table");

                struct timeval tb1, te1;
                struct timeval tb2, te2;
                float a1 = 0, a2 = 0;
                for(int i = 1; i <= 1000; i++)
                {
                    f_load_table(str, &d_t2);
                    f_create_key_table(&t_k2, &d_t2);
                    gettimeofday(&tb1, NULL);
                    f_sort_bubble_key(&t_k2);
                    gettimeofday(&te1, NULL);
                    a1 += (float)(te1.tv_usec - tb1.tv_usec) / 1000000 + (float)(te1.tv_usec - tb1.tv_usec);

                    gettimeofday(&tb2, NULL);
                    f_sort_table_bubble(&d_t2);
                    gettimeofday(&te2, NULL);
                    a2 += (float)(te2.tv_usec - tb2.tv_usec) / 1000000 + (float)(te2.tv_usec - tb2.tv_usec);
                }
                

                printf("|%-15s|%-10f|%-10f|\n", "The bubble sort", a2/1000, a1/1000);

                float sum1 = (float)(te2.tv_usec - tb2.tv_usec) / 1000000 + (float)(te2.tv_usec - tb2.tv_usec) + (float)(te1.tv_usec - tb1.tv_usec) / 1000000 + (float)(te1.tv_usec - tb1.tv_usec);
                float sum3 = (float)(te1.tv_usec - tb1.tv_usec) / 1000000 + (float)(te1.tv_usec - tb1.tv_usec);
                float sum4 = (float)(te2.tv_usec - tb2.tv_usec) / 1000000 + (float)(te2.tv_usec - tb2.tv_usec);
                a1 = 0, a2 = 0;
                for(int i = 1; i <= 1000; i++)
                {   
                    f_load_table(str, &d_t1);
                    f_create_key_table(&t_k1, &d_t1);
                    gettimeofday(&tb1, NULL);
                    f_sort_insert_key(&t_k1);
                    gettimeofday(&te1, NULL);
                    a1 += (float)(te1.tv_usec - tb1.tv_usec) / 1000000 + (float)(te1.tv_usec - tb1.tv_usec);

                    gettimeofday(&tb2, NULL);
                    f_sort_table(&d_t1);
                    gettimeofday(&te2, NULL);
                    a2 += (float)(te2.tv_usec - tb2.tv_usec) / 1000000 + (float)(te2.tv_usec - tb2.tv_usec);
                }

                printf("|%-15s|%-10f|%-10f|\n\n", "The insert sort", a2/1000, a1/1000);

                float sum2 = (float)(te2.tv_usec - tb2.tv_usec) / 1000000 + (float)(te2.tv_usec - tb2.tv_usec) + (float)(te1.tv_usec - tb1.tv_usec) / 1000000 + (float)(te1.tv_usec - tb1.tv_usec);

                printf("The efficiency of the insert sort compared to bubble "
                    "sort: %.2f%%\n\n", (sum2 / sum1 * 100));

                printf("The efficiency of the sorted table with key table "
                    "compared to sorted table without key table "
                    "sort: %.2f%%\n\n", (sum3 / sum4 * 100));

                printf("Size of table of students: %lu "
                    "b\n\n", (sizeof(struct data) * d_t1.n));
                printf("Size of table of keys: %lu "
                    "b\n\n", (sizeof(struct key) * t_k1.n));
                break;
            }
            case 0:
                return OK;
            default:
            {
                printf("Error input\n");
                break;
            }
        }
    }
}