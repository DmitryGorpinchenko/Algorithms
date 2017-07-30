#include <stdio.h>
#include <stdlib.h>

int comparator(const void *a, const void *b);
void qsort3way(int *a, int n);
void qsort3way_rec(int *a, int lo, int hi);
void partition3way(int *a, int lo, int hi, int *m1, int *m2);
int get_pivot(int *a, int lo, int hi);
void swap(int *a, int i, int j);

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
	
	//qsort(a, n, sizeof(int), comparator);
	qsort3way(a, n);
	
	for(int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	
	free(a);
	return 0;
}

void qsort3way(int *a, int n) {
	
	qsort3way_rec(a, 0, n);
}

void qsort3way_rec(int *a, int lo, int hi) {
	
	if(hi - lo <= 1) {
		return;
	}
	
	int m1, m2;
	partition3way(a, lo, hi, &m1, &m2);
	
	qsort3way_rec(a, lo, m1);
	qsort3way_rec(a, m2, hi);
}

void partition3way(int *a, int lo, int hi, int *m1, int *m2) {
	
	int pivot_id = get_pivot(a, lo, hi);
	swap(a, lo, pivot_id);
	
	int pivot = a[lo];
	int lt = lo, gt = hi - 1, i = lo;
	while (i <= gt) {
		int cmp = comparator(&a[i], &pivot);
		if(cmp < 0) {
			swap(a, lt++, i++);
		} else if(cmp > 0) {
			swap(a, i, gt--);
		} else {
			i++;
		}
	}

	*m1 = lt;
	*m2 = gt + 1;
}

int get_pivot(int *a, int lo, int hi) {

	int pivot = lo;
	int mid = lo + (hi - lo) / 2;
	
	if(a[mid] > a[lo] && a[mid] < a[hi - 1]) {
		pivot = mid;
	} else if(a[hi - 1] > a[lo] && a[hi - 1] < a[mid]) {
		pivot = hi - 1;
	}
	
	return pivot; 
}

void swap(int *a, int i, int j) {
	
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

int comparator(const void *a, const void *b) {
	
	int *aa = (int*) a;
	int *bb = (int*) b;
	
	return *aa - *bb;
}
