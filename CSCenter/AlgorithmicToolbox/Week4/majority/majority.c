#include <stdio.h>
#include <stdlib.h>

int has_majority(int *a, int n);
int majority(int *a, int lo, int hi);

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
	
	printf("%d\n", has_majority(a, n));

	free(a);
	return 0;
}

int has_majority(int *a, int n) {
	
	return majority(a, 0, n) != -1;
}

int majority(int *a, int lo, int hi) {
	
	if(hi - lo < 1) {
		return -1;
	} else if(hi - lo == 1) {
		return a[lo];
	}
	
	int mid = lo + (hi - lo) / 2;
	int lmaj = majority(a, lo, mid);
	int rmaj = majority(a, mid, hi);
	
	int lcount = 0, rcount = 0;
	for(int i = lo; i < hi; i++) {
		lcount = (a[i] == lmaj) ? lcount + 1 : lcount; 
		rcount = (a[i] == rmaj) ? rcount + 1 : rcount; 
	}
	
	if(lcount > (hi - lo) / 2) {
		return lmaj;
	} else if(rcount > (hi - lo) / 2) {
		return rmaj;
	}
	return -1;
}
