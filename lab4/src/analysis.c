#include "analysis.h"
#include "structs.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void analysis(void)
{
    arr_stack_t arr[MAX_STACK_SIZE];
    arr->cur_size = 0;
    list_stack_t *list = NULL, *list1 = NULL;
    uint64_t start, end, time_push = 0, time_pop = 0, time_palindrom = 0, time = 0;
    free_areas_t areas;
    areas.arr = NULL;

    int cnt ;
    printf("Введите количество элементов для анализма (<= %d): ", MAX_STACK_SIZE);
    scanf("%d", &cnt);
    if (cnt < 1 || cnt > MAX_STACK_SIZE)
    {
        printf("Не меньше 1 или больше %d\n", MAX_STACK_SIZE);
        return;
    }
    printf("\n");
    printf("Массив: \n\n");
    for (int i = 0; i < 1000; i++)
    {
        start = tick();
        for (int i = 0; i < cnt; i++)
            array_push(arr, 'a');
        end = tick();
        
        time_push += end - start;
        

        start = tick();
        array_is_palindrome(arr);
        end = tick();
        
        time_palindrom += end - start;
        
        
        char ch;
        start = tick();
        for (int i = 0; i < cnt; i++)
            array_pop(arr, &ch);
        end = tick();
        
        time_pop += end - start;
    }

    printf("Время добавления %d элементов: %ld тактов\n", cnt, time_push/1000);

    printf("Время проверки строки из %d символов на палиндром: %ld тактов\n", cnt, time_palindrom/1000);
    
    printf("Время удаления %d элементов: %ld тактов\n\n", cnt, time_pop/1000);

    printf("Занимаемая %d элементами память: %ld байт\n\n", cnt, sizeof(arr_stack_t));

    printf("Список: \n\n");
    char ch;
    int first = 1;
    start = tick();
    for (int i = 0; i < cnt; i++)
    {
        list_push(&list, 'a', first);
        first = 0;
    }
    end = tick();
    
    time = end - start;
    printf("Время добавления %d элементов: %ld тактов\n", cnt, time);

    start = tick();
    list_is_palindrome(&list, &areas);
    end = tick();
    
    time = end - start;
    printf("Время проверки строки из %d символов на палиндром: %ld тактов\n", cnt, time);

    size_t addr;
    for (int i = 0; i < cnt; i++)
        list_pop(&list, &ch, &addr);

    first = 1;
    for (int i = 0; i < cnt; i++)
    {
        list_push(&list1, 'a', first);
        first = 0;
    }

    size_t addr1;
    start = tick();
    for (int i = 0; i < cnt; i++)
        list_pop(&list1, &ch, &addr1);
    end = tick();
    
    time = end - start;
    printf("Время удаления %d элементов: %ld тактов\n\n", cnt, time);

    printf("Занимаемая %d элементами память: %ld байт\n\n", cnt, sizeof(list_stack_t) * cnt);
    free_list(&list);
    free_list(&list1);
}
