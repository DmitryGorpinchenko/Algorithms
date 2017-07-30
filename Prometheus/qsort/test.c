#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qsort.h"

int cmp_int(void *a, void *b);

int main(int argc, char **argv)
{
	if (argc != 2) {
		return -1;
	}
	
	FILE *f = fopen(argv[1], "r");
	
	if (f == NULL) {
		return -1;
	}

	int size;
	fscanf(f, "%d", &size);

	int original_arr[size];
	for (int i = 0; i < size; i++) {
		fscanf(f, "%d", original_arr + i);
	}
	int arr[size];

	init_stats();
	memcpy(arr, original_arr, sizeof(int) * size);
	q_sort(arr, sizeof(int), size, LAST, cmp_int);
	printf("LAST:   cmp_num = %ld\n", cmp_num());
	
	init_stats();
	memcpy(arr, original_arr, sizeof(int) * size);
	q_sort(arr, sizeof(int), size, FIRST, cmp_int);
	printf("FIRST:  cmp_num = %ld\n", cmp_num());

	init_stats();
	memcpy(arr, original_arr, sizeof(int) * size);
	q_sort(arr, sizeof(int), size, MEDIAN, cmp_int);
	printf("MEDIAN: cmp_num = %ld\n", cmp_num());
	
	fclose(f);
	return 0;
} 

int cmp_int(void *a, void *b)
{
	return *(int *) a < *(int *) b;
}
