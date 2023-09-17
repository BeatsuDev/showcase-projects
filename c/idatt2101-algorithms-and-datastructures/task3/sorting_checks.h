#ifndef SORTING_CHECKS_H
#define SORTING_CHECKS_H

#include <time.h>

long is_sorted(long *array, long array_size)
{
    for (long i = 0; i < array_size - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

long check_sum(long *array, long array_size)
{
    long sum = 0;
    for (long i = 0; i < array_size; i++)
    {
        sum += array[i];
    }
    return sum;
}

double time_sort(void (*function)(long *, long, long), long *array, long array_size)
{
    clock_t start = clock();
    function(array, 0, array_size - 1);
    clock_t end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

double time_counting_sort(void (*counting_sort)(long *, long, long, long, long), long *array, long array_size)
{
    clock_t start = clock();
    long min, max;
    for (long i = 0; i < array_size; i++)
    {
        if (i == 0) min = max = array[i];
        else
        {
            if (array[i] < min) min = array[i];
            if (array[i] > max) max = array[i];
        }
    }
    counting_sort(array, 0, array_size - 1, min, max);
    clock_t end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

#endif