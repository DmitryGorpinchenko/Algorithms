#include <stdio.h>
#include <stdlib.h>

int binary_search(int *a, int lo, int hi, int elem);
void find_ids(int *a, int n, int *b, int k, int* ids);

int main() {
	
	int n;
	if(scanf("%d", &n) != 1) {
		return 1;
	}
	
	int *a = malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++) {
		if(scanf("%d", &a[i]) != 1) {
			return 1;
		}
	}
	
	int k;
	if(scanf("%d", &k) != 1) {
		return 1;
	}
	
	int *b = malloc(sizeof(int) * k);
	for(int i = 0; i < k; i++) {
		if(scanf("%d", &b[i]) != 1) {
			return 1;
		}
	}
	
	int *ids = malloc(sizeof(int) * k);
	find_ids(a, n, b, k, ids);
	
	for(int i = 0; i < k; i++) {
		printf("%d ", ids[i]);
	}
	printf("\n");
	
	free(a);
	free(b);
	free(ids);
	return 0;
}

void find_ids(int *a, int n, int *b, int k, int* ids) {
	
	for(int i = 0; i < k; i++) {
		ids[i] = binary_search(a, 0, n, b[i]);
	}
}

int binary_search(int *a, int lo, int hi, int elem) {
	
	while(lo <= hi) {
		int mid = lo + (hi - lo)/2;
		if(elem < a[mid]) {
			hi = mid - 1;
		} else if(elem > a[mid]) {
			lo = mid + 1;
		} else {
			return mid;
		}	
	}
	
	return -1;
}
