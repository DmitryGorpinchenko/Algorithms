#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t inversions(int *a, int n);
void merge_inv(int *a, int *aux, int lo, int hi, uint64_t *inv_count);
void merge(int *a, int *aux, int lo, int mid, int hi, uint64_t *inv_count);

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
	
	printf("%llu\n", inversions(a, n));
	
	free(a);
	return 0;
}

uint64_t inversions(int *a, int n) {
	
	uint64_t inv_count = 0;
	int *aux = malloc(sizeof(int) * n);
	merge_inv(a, aux, 0, n, &inv_count);
	free(aux);
	return inv_count;
}

void merge_inv(int *a, int *aux, int lo, int hi, uint64_t *inv_count) {
	
	if(hi - lo <= 1) {
		return;
	}
	
	int mid = lo + (hi - lo) / 2;
	
	merge_inv(a, aux, lo, mid, inv_count);
	merge_inv(a, aux, mid, hi, inv_count);
	
	merge(a, aux, lo, mid, hi, inv_count);
}

void merge(int *a, int *aux, int lo, int mid, int hi, uint64_t *inv_count) {
	
	for(int i = lo; i < hi; i++) {
		aux[i] = a[i];
	}
	
	int lp = lo, rp = mid, i = lo;
	while(lp < mid && rp < hi) {
		a[i++] = (aux[lp] <= aux[rp]) ? aux[lp++] : ((*inv_count) += (mid - lp), aux[rp++]);
	}
	
	while(i < hi) {
		a[i++] = (lp < mid) ? aux[lp++] : aux[rp++]; 
	}
}
