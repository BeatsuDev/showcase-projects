#ifndef SORTING_H
#define SORTING_H

#include <stdbool.h>
#include "swap.h"

void bubble_sort(long *array, long start, long end)
{
    for (long i = start; i < end; i++)
        for (long j = start; j < end - (i - start); j++)
            if (array[j] > array[j + 1]) swap(&array[j], &array[j + 1]);
}

void comb_sort(long *array, long start, long end)
{
    long gap = end - start;
    const float shrink_factor = 1.3;
    bool swapped;

    do
    {
        gap = (long) (gap / shrink_factor);
        if (gap < 1) gap = 1;

        swapped = false;

        for (long i = start; i + gap <= end; i++)
        {
            if (array[i] > array[i + gap])
            {
                swap(&array[i], &array[i + gap]);
                swapped = true;
            }
        }
    } while (gap > 1 || swapped);
}

void counting_sort(long *array, long start, long end, long min, long max)
{
    long *count = calloc(max - min + 1, sizeof(long));
    for (long i = start; i <= end; i++) count[array[i] - min]++;
    for (long i = min, j = start; i <= max; i++)
        while (count[i - min]-- > 0) array[j++] = i;
    free(count);
}

// Sorts 1, 2 or 3 numbers in an array and returns the median index
long median3sort(long *array, long start_index, long end_index)
{
    long middle_index = (start_index + end_index) / 2;
    if (array[start_index] > array[middle_index]) swap(&array[start_index], &array[middle_index]);
    if (array[middle_index] > array[end_index])
    {
        swap(&array[middle_index], &array[end_index]);
        if (array[start_index] > array[middle_index]) swap(&array[start_index], &array[middle_index]);
    }
    return middle_index;
}

long split(long *array, long start, long end)
{
    long pivot_index = median3sort(array, start, end);
    long pivot_value = array[pivot_index];

    // Move the pivot element to the second to last position in the array
    swap(&array[pivot_index], &array[end - 1]);

    long left_index = start;
    long right_index = end - 1;
    while (true)
    {
        while (array[++left_index] < pivot_value);
        while (array[--right_index] > pivot_value);
        if (left_index >= right_index) break;
        swap(&array[left_index], &array[right_index]);
    }

    // Move back the pivot element
    swap(&array[left_index], &array[end - 1]);
    return left_index;
}

void quicksort(long *array, long start, long end)
{
    if (end - start <= 2)
        return (void) median3sort(array, start, end);

    long pivot_point = split(array, start, end);
    quicksort(array, start, pivot_point - 1);
    quicksort(array, pivot_point + 1, end);
}

/**
 * Improved quicksort that uses count sort for arrays with small range of values.
 * Assumes that the indexes start=0 and end=array_length OR start-1 and end+1 are
 * previous quicksort pivot points and that all values in the array are between
 * the values at start-1 and end+1.
 */
void quicksort_improved(long *array, long start, long end)
{
    // Find min and max values in the array, then move them to the beginning and end
    // if the start or end index is the first or last index in the array.
    if (start == 0)
    {
        long min_index, max_index;
        for (long i = start; i <= end; i++)
        {
            if (array[i] < array[min_index]) min_index = i;
            if (array[i] > array[max_index]) max_index = i;
        }
        swap(&array[start], &array[min_index]);
        swap(&array[end], &array[max_index]);

        start += 1;
        end -= 1;
    }

    // All values are equal! Let's return early!
    if (array[start-1] == array[end+1])
        return;

    // Normal quicksort
    if (end - start <= 2)
        return (void) median3sort(array, start, end);

    int pivot_point = split(array, start, end);
    quicksort_improved(array, start, pivot_point - 1);
    quicksort_improved(array, pivot_point + 1, end);
}

#endif
