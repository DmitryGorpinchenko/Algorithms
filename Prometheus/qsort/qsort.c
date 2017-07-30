#include <stdio.h>
#include <string.h>
#include "qsort.h"

#ifdef STATS
static int64_t last_cmp_num = 0;
#endif

int part(void *arr, int el_sz, int el_num, enum Pivot p, comparator cmp);
void *median3(void *a, void *b, void *c, comparator cmp);

void q_sort(void *arr, int el_sz, int el_num, enum Pivot p, comparator cmp)
{           
	if (el_num <= 1) {
		return;
	}
	
	int pivot = part(arr, el_sz, el_num, p, cmp);
	
	if (pivot < 0) {
		return;
	}
	
	void *arr_l = arr;
	void *arr_r = (char *) arr + el_sz * (pivot + 1);

	q_sort(arr_l, el_sz, pivot, p, cmp);
	q_sort(arr_r, el_sz, el_num - pivot - 1, p, cmp);
}

int part(void *arr, int el_sz, int el_num, enum Pivot p, comparator cmp)
{
	void *first = arr;
	void *last  = ((char *) arr) + (el_num - 1) * el_sz;
	void *mid   = ((char *) arr) + (el_num - 1) / 2 * el_sz; /* WARNING: order of / and * matters here! */

	void *pivot;

	switch (p) {
	case FIRST:  pivot = first;                          break;
	case LAST:   pivot = last;                           break;
	case MEDIAN: pivot = median3(first, mid, last, cmp); break;
	default:     pivot = NULL;                           break;
	}
	if (pivot == NULL) {
		return -1;
	}

	int i = -1;
	char tmp[el_sz];
	
	if (pivot != last) { /* swap pivot with last */
		memcpy(tmp, pivot, el_sz);
		memcpy(pivot, last, el_sz);
		memcpy(last, tmp, el_sz);
		pivot = last;
	}
	for (int j = 0; j < el_num - 1; j++) {
		if (cmp(pivot, (char *) arr + el_sz * j)) {
			continue;
		}
		if (++i != j) {
			memcpy(tmp, (char *) arr + el_sz * i, el_sz);
			memcpy((char *) arr + el_sz * i, (char *) arr + el_sz * j, el_sz);
			memcpy((char *) arr + el_sz * j, tmp, el_sz);
		}
	}
	if (++i != el_num - 1) {
		memcpy(tmp, (char *) arr + el_sz * i, el_sz);
		memcpy((char *) arr + el_sz * i, last, el_sz);
		memcpy(last, tmp, el_sz);
	}
#ifdef STATS
	last_cmp_num += el_num - 1;
#endif
	return i;	
}

void init_stats(void)
{
#ifdef STATS
	last_cmp_num = 0;
#endif
}

int64_t cmp_num(void)
{
#ifdef STATS
	return last_cmp_num;
#else
	printf("STATS must be defined to collect statistics!\n");
	return -1;
#endif
}

void *median3(void *a, void *b, void *c, comparator cmp)
{
	if ((!cmp(a, b) && !cmp(c, a)) || (!cmp(a, c) && !cmp(b, a))) {
		return a;
	}
	if ((!cmp(b, a) && !cmp(c, b)) || (!cmp(b, c) && !cmp(a, b))) {
		return b;
	}
	return c;
}
