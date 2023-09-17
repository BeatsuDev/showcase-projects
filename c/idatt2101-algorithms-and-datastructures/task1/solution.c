#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// For saving the index and the price value at that index
struct IndexedValue {
    int index;
    int value;
};

// The best time to buy and sell the stock
struct GreatestProfit {
    int buy_index;
    int sell_index;
    int profit;
};

/* The task solution.
 *
 * This solution runs in Θ(n). Both worst case and best case scenarios run
 * a loop through the price_changes once, and only once, to find a solution.
 */ 
struct GreatestProfit solution(int *price_changes, int size) {
    int price = 0;
    struct IndexedValue lowest_point  = { 0, 0 };
    struct GreatestProfit greatest_profit = { 0, 0, -1.0/0.0 };

    for (int i = 0; i < size; i++) {
        price += price_changes[i];

        // Update the lowest point if the price is at a new global minimum
        if (price < lowest_point.value) {
            lowest_point = (struct IndexedValue){i, price};
        }

        // If the price beats the current greatest profit, update the greatest profit
        if (price - lowest_point.value > greatest_profit.profit) {
            greatest_profit = (struct GreatestProfit){ lowest_point.index, i, price - lowest_point.value };                
        }    
    }

    return greatest_profit;
}

// Populates an array with random data for testing
void populate_dummy_data(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 20 - 10;
    }
}

// Times the solution for datasize of n and returns average execution time in milliseconds
double time_solution(int n) {
    int *price_changes = malloc(sizeof(int) * n);  // Heap allocation to avoid stack overflow
    populate_dummy_data(price_changes, n);

    long executions = 0;

    clock_t start = clock();
    while (clock() - start < CLOCKS_PER_SEC) {  // Run for 1 second
        solution(price_changes, n);
        executions++;
    }
    free(price_changes);

    return 1000.0 / executions;  // Return the average time in milliseconds per execution
}

int main() {
    // The example from the assignment
    int price_changes[] = {-1, 3, -9, 2, 2, -1, 2, -1, -5};
    struct GreatestProfit greatest_profit = solution(price_changes, sizeof(price_changes)/sizeof(int));
    printf(
        "Greatest profit is if you buy after day %d and sell after day %d. Profit: %d\n\n",
        greatest_profit.buy_index,
        greatest_profit.sell_index,
        greatest_profit.profit
    );

    // Testing the time complexity with pseudorandom data (with a seed of 0 to make it deterministic)
    puts("Now time testing the solution with the psueodrandom data");
    
    srand(0);
    double execution_times[5]; 

    // Run 5 times, each a factor of 10 larger. O(n) results should give a factor of 10 increase in time
    // for each increase in n. O(n^2) results should give a factor of 100 increase, and so on.
    for (int i = 0; i < 5; i++) {
        double execution_time = time_solution( pow(10, i+3) );
        printf("Time per execution for n = %d: %.3fms", i, execution_time);

        execution_times[i] = execution_time;
        if (i > 0 && execution_times[i-1] > 0) {
            printf(", increased by a factor of: %.3fx", execution_times[i] / execution_times[i-1]);
        }
        puts("");  // Newline
    }

    return 0;
}
