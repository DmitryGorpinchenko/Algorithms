#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

typedef uint8_t bool;

int primitive_calc(int n, bool *trace);
int min(int a, int b);

int main() {
	
	int n;
	if(scanf("%d", &n) != 1) {
		return 1;
	}
	
	bool *trace = calloc(n + 1, sizeof(bool));
	
	printf("%d\n", primitive_calc(n, trace));
	
	for(int i = 1; i <= n; i++) {
		if(trace[i] == 1) {
			printf("%d ", i);
		}
	}
	printf("\n");
	
	return 0;
}

int primitive_calc(int n, bool *trace) {
	
	int *op_nums = malloc(sizeof(int) * (n + 1));
	
	op_nums[0] = 0;
	op_nums[1] = 0;
	
	for(int i = 2; i <= n; i++) {
		op_nums[i] = op_nums[i - 1] + 1;
		if(i % 2 == 0) {
			op_nums[i] = min(op_nums[i], op_nums[i / 2] + 1); 
		} 
		if(i % 3 == 0) {
			op_nums[i] = min(op_nums[i], op_nums[i / 3] + 1); 
		}
	}
	
	int res = op_nums[n];
	
	int i = n;
	trace[n] = 1;
	while(i > 1) {
		if(op_nums[i] == op_nums[i - 1] + 1) {
			trace[--i] = 1;
		} else if(i % 2 == 0 && op_nums[i] == op_nums[i / 2] + 1) {
			trace[i /= 2] = 1;
		} else if(i % 3 == 0 && op_nums[i] == op_nums[i / 3] + 1) {
			trace[i /= 3] = 1;
		}
	}
	
	free(op_nums);
	return res;
}

int min(int a, int b) {
	
	return a < b ? a : b;
}
