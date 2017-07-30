#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t max_pairwise_product(const int *numbers, int n) {
   
	int max1_id = -1; 
	int max1 = -1;
	for(int i = 0; i < n; i++) {
		if(max1 < numbers[i]) {
			max1 = numbers[i];
			max1_id = i;
		}
	}

	int max2_id = -1; 
	int max2 = -1;
	for(int i = 0; i < n; i++) {
		if(max1_id != i && max2 < numbers[i]) {
			max2 = numbers[i];
			max2_id = i;
		}
	}

	return ((uint64_t) max1) * max2;
}

int main() {

	int n;
	
	if(scanf("%d", &n) != 1) {
		return 1;
	}

	int *numbers = malloc(sizeof(int) * n);
	for (int i = 0; i < n; ++i) {
		if(scanf("%d", numbers + i) != 1) {
			return 1;
		}
	}
	
	uint64_t result = max_pairwise_product(numbers, n);
	printf("%llu\n", result);
	
	free(numbers);

	return 0;
}
