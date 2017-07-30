#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	char type;
	int id;
} point;

typedef struct {
	int a;
	int b;
} segment;

void init_segment(segment *seg, int a, int b);
void init_point(point *p, int x, char type, int id);
void count_segments(segment *segs, int s, int *x, int p, int *seg_counts);
void fill_counts(point *points, int s, int p, int *seg_counts);
int comparator(const void* p1, const void* p2);

int main() {
	
	int s, p;
	if(scanf("%d%d", &s, &p) != 2) {
		return 1;
	}
	
	segment *segs = malloc(sizeof(segment) * s);
	for(int i = 0; i < s; i++) {
		int a, b;
		if(scanf("%d%d", &a, &b) != 2) {
			return 1;
		}
		init_segment(segs + i, a, b);
	}
	
	int *x = malloc(sizeof(int) * p);
	for(int i = 0; i < p; i++) {
		if(scanf("%d", &x[i]) != 1) {
			return 1;
		}
	}	
	
	int *seg_counts = calloc(p, sizeof(int));
	count_segments(segs, s, x, p, seg_counts);
	
	for(int i = 0; i < p; i++) {
		printf("%d ", seg_counts[i]);
	}
	printf("\n");
	
	free(segs);
	free(x);
	free(seg_counts);
	return 0;
}

void count_segments(segment *segs, int s, int *x, int p, int *seg_counts) {
	
	point *points = malloc(sizeof(point) * (2 * s + p));
	
	int p_num = 0;
	for(int i = 0; i < s; i++) {
		init_point(points + p_num++, segs[i].a, 'l', -1);
		init_point(points + p_num++, segs[i].b, 'r', -1);
	}
	for(int i = 0; i < p; i++) {	
		init_point(points + p_num++, x[i], 'p', i);
	}
	
	qsort(points, 2 * s + p, sizeof(point), comparator);
	
	fill_counts(points, s, p, seg_counts);
	
	free(points);
}

void fill_counts(point *points, int s, int p, int *seg_counts) {
	
	int opened = 0;
	for(int i = 0; i < 2 * s + p; i++) {
		if(points[i].type == 'l') {
			++opened;
		} else if(points[i].type == 'r') {
			--opened;
		} else {
			seg_counts[points[i].id] = opened;	
		}
	}
}

void init_segment(segment *seg, int a, int b) {
	
	seg->a = a;
	seg->b = b;
}

void init_point(point *p, int x, char type, int id) {
	
	p->x = x;
	p->type = type;
	p->id = id;
}

int comparator(const void* p1, const void* p2) {
	
	point *point1 = (point*) p1;
	point *point2 = (point*) p2;
	
	if(point1->x < point2->x) {
		return -1;
	} else if(point1->x > point2->x) {
		return 1;
	} else if(point1->type < point2->type) {
		return -1;
	} else if(point1->type > point2->type) {
		return 1;
	}
	return 0;
}
