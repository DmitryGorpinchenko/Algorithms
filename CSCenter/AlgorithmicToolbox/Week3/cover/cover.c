#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
	int a;
	int b;
	uint8_t is_covered;
} Segment;

void init_segment(Segment* seg, int a, int b);
int comparator(const void* s1, const void* s2);
int cover(Segment* segs, int* res, int n);

int main() {
	
	int n;
	if(scanf("%d", &n) != 1) {
		return 1;
	}
	
	Segment* segs = malloc(sizeof(Segment) * n);
	
	int a, b;
	for(int i = 0; i < n; i++) {
		if(scanf("%d%d", &a, &b) != 2) {
			return 1;
		}
		init_segment(segs + i, a, b);	
	}
	
	int* res = malloc(sizeof(int) * n);
	int m = cover(segs, res, n);
	
	printf("%d\n", m);
	for(int i = 0; i < n; i++) {
		if(res[i] < 0) {
			break;
		}
		printf("%d ", res[i]);
	}
	printf("\n");
	
	free(res);
	free(segs);
	return 0;	
}

int cover(Segment* segs, int* res, int n) {
	
	int m = 0;
	
	for(int i = 0; i < n; i++) {
		res[i] = -1;
	}
	
	qsort(segs, n, sizeof(Segment), comparator);
	
	int point;
	for(int i = 0; i < n; i++) {
		if(segs[i].is_covered) {
			continue;
		}
		point = segs[i].b;
		res[m] = point;
		m++;
		for(int j = i; j < n; j++) {
			if(segs[j].a <= point && point <= segs[j].b) {
				segs[j].is_covered = 1;
			}
		}
	}
	
	return m;
}

int comparator(const void* s1, const void* s2) {
		
	Segment* seg1 = (Segment*) s1;
	Segment* seg2 = (Segment*) s2;
	
	if(seg1->b < seg2->b) {
		return -1;
	} else if(seg1->b > seg2->b) {
		return 1;
	}
	return 0;
}

void init_segment(Segment* seg, int a, int b) {
	
	seg->a = a;
	seg->b = b;
	seg->is_covered = 0;
}
