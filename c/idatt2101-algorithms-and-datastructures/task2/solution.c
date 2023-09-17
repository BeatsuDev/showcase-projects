#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double time_method(double (*multiply)(unsigned int n, double x), int n, double x, unsigned int runs);

double multiply1(unsigned int n, double x)
{	
	if (n == 0) return 0;
	if (n == 1) return x;
	return x + multiply1(n-1, x);
}

double multiply2(unsigned int n, double x)
{
	if (n == 0) return 0;
	if (n == 1) return x;
	if (n & 1) return x + multiply2((n-1) / 2, x + x);
	else return multiply2(n/2, x + x);
}


int main() 
{
	int n1 = 5;
	int n2 = 10000;
	double x1 = 2.5;
	double x2 = 4.44; 

	printf("Method 1: %d * %f = %f\n", n1, x1, multiply1(n1, x1));
	printf("Method 1: %d * %f = %f\n", n2, x2, multiply1(n2, x2));
	printf("Method 2: %d * %f = %f\n", n1, x1, multiply2(n1, x1));
	printf("Method 2: %d * %f = %f\n", n2, x2, multiply2(n2, x2));


	// Time the methods
	// Use a predefined set of random numbers for both methods for exactly the same runs:
	int input_size = 10000;
	int n_inputs[input_size];
	double x_inputs[input_size];

	for (int i = 0; i < 10000; i++)
	{
		n_inputs[i] = rand() % 1000;
		x_inputs[i] = rand() / RAND_MAX * 1000;
	}

	printf("Method 1 timings:\n");
	for (unsigned int n = 10000; n <= 100000; n += 10000)
	{
		printf("n = %d, time = %lfms\n", n, time_method(multiply1, n, 1.01, 100));
	}
	
	printf("Method 2 timings:\n");
	for (unsigned int n = 100; n < 1000000; n *= 2)
	{
		printf("n = %d, time = %lfms\n", n, time_method(multiply2, n, 1.01, 100));
	}

	return 0;
}

double time_method(double (*multiply)(unsigned int n, double x), int n, double x, unsigned int runs)
{
	clock_t start = clock();
	for (int i = 0; i < runs; i++)
	{
		multiply(n, x);
	}
	clock_t end = clock();
	
	// Return time in milliseconds
	return (double) (end - start) / (CLOCKS_PER_SEC / 1000);	
}
	
