#include <stdio.h>
#include <stdlib.h>

#include "sorting.h"
#include "sorting_checks.h"

void print(int *array, int size)
{
    for (int i = 0; i < size; i++) printf("%d ", array[i]);
    printf("\n");
}

int main()
{
    // Seed the random number generator:
    srand(time(NULL));

    long array_size = 10 * 1000 * 1000;
    long *array1 = malloc(sizeof(long) * array_size);
    long *array2 = malloc(sizeof(long) * array_size);
    long *array3 = malloc(sizeof(long) * array_size);
    long *array4 = malloc(sizeof(long) * array_size);

    // Fill the array with random numbers between 0 and 1 million:
    puts("Creating the arrays...");
    for (long i = 0; i < array_size; i++)
    {
        long random = rand();
        array1[i] = random % (array_size / 10000);  // I gjennomsnitt 100 duplikater
        array2[i] = random % (array_size / 10000);  // I gjennomsnitt 100 duplikater
        array3[i] = random % (array_size * 100);  // 1% sjanse for duplikat
        array4[i] = random % (array_size * 100);  // 1% sjanse for duplikat
    }
    puts("Created the arrays...\n");

    puts("Testing quicksort on an array with a lot of duplicates...");
    long before_checksum = check_sum(array1, array_size);
    double seconds_elapsed = time_sort(quicksort, array1, array_size);
    long after_checksum = check_sum(array1, array_size);
    printf("Sorting took %f seconds. ", seconds_elapsed);
    
    if (before_checksum == after_checksum) printf("Checksums match. ");
    else printf("WRONG CHECKSUM! ");

    if (is_sorted(array1, array_size)) printf("Array is sorted.\n\n");
    else printf("WRONG SORT!\n\n");


    puts("Testing quicksort improved version with a lot of duplicates...");
    before_checksum = check_sum(array2, array_size);
    seconds_elapsed = time_sort(quicksort_improved, array2, array_size);
    after_checksum = check_sum(array2, array_size);
    printf("Sorting took %f seconds. ", seconds_elapsed);

    if (before_checksum == after_checksum) printf("Checksums match. ");
    else printf("WRONG CHECKSUM! ");

    if (is_sorted(array2, array_size)) printf("Array is sorted.\n\n");
    else printf("WRONG SORT!\n\n");


    puts("Testing quicksort with 1\% duplicates...");
    before_checksum = check_sum(array3, array_size);
    seconds_elapsed = time_sort(quicksort, array3, array_size);
    after_checksum = check_sum(array3, array_size);
    printf("Sorting took %f seconds. ", seconds_elapsed);

    if (before_checksum == after_checksum) printf("Checksums match. ");
    else printf("WRONG CHECKSUM! ");

    if (is_sorted(array3, array_size)) printf("Array is sorted.\n\n");
    else printf("WRONG SORT!\n\n");


    puts("Testing improved quicksort with 1\% duplicates...");
    before_checksum = check_sum(array4, array_size);
    seconds_elapsed = time_sort(quicksort_improved, array4, array_size);
    after_checksum = check_sum(array4, array_size);
    printf("Sorting took %f seconds. ", seconds_elapsed);

    if (before_checksum == after_checksum) printf("Checksums match. ");
    else printf("WRONG CHECKSUM! ");

    if (is_sorted(array4, array_size)) printf("Array is sorted.\n\n");
    else printf("WRONG SORT!\n\n");


    puts("Testing improved quicksort with 1\% duplicates already sorted...");
    before_checksum = check_sum(array4, array_size);
    seconds_elapsed = time_sort(quicksort_improved, array4, array_size);
    after_checksum = check_sum(array4, array_size);
    printf("Sorting took %f seconds. ", seconds_elapsed);

    if (before_checksum == after_checksum) printf("Checksums match. ");
    else printf("WRONG CHECKSUM! ");

    if (is_sorted(array4, array_size)) printf("Array is sorted.\n\n");
    else printf("WRONG SORT!\n\n");
}
