#include <stdio.h>
#include <stdlib.h>

int knapsack(int *items, int n, int W);

int main() {
	
	int W, n;
	if(scanf("%d%d", &W, &n) != 2) {
		return 1;
	}
	
	int *w = malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++) {
		if(scanf("%d", &w[i]) != 1) {
			return 1;
		}
	}
	
	printf("%d\n", knapsack(w, n, W));
	
	free(w);
	return 0;
}

int knapsack(int *items, int n, int W) {
	
	int *val = malloc(sizeof(int) * (n + 1) * (W + 1));
	#define val(i, j) val[(i) * (W + 1) + (j)]
	
	for(int i = 0; i <= W; i++) {
		val(0, i) = 0;
	}
	for(int i = 0; i <= n; i++) {
		val(i, 0) = 0;
	}
	
	for(int i = 1; i <= n; i++) {
		int vi = items[i - 1];
		int wi = items[i - 1];
		for(int w = 1; w <= W; w++) {
			val(i, w) = val(i - 1, w);
			if(w >= wi) {
				int tmp = val(i - 1, w - wi) + vi;
				if(val(i, w) < tmp) {
					val(i, w) = tmp;
				}
			}
		}
	}
	int optValue = val(n, W);
	
	free(val);
	return optValue;
}
