#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int v;
	int w;
} Item;

void init_item(Item* item, int v, int w);
double fill_knapsack(Item* items, int n, int W);
int comparator(const void* i1, const void* i2);

int main() {
	
	int n, W;
	if(scanf("%d%d", &n, &W) != 2) {
		return 1;
	}
	
	Item* items = malloc(sizeof(Item) * n);
	
	int v, w;
	for(int i = 0; i < n; i++) {
		if(scanf("%d%d", &v, &w) != 2) {
			return 1;
		}
		init_item(items + i, v, w);	
	}
	
	printf("%f\n", fill_knapsack(items, n, W));
	
	free(items);
	return 0;
}

double fill_knapsack(Item* items, int n, int W) {
	
	qsort(items, n, sizeof(Item), comparator);
	
	double value = 0.0;
	for(int i = 0; i < n; i++) {
		if(W == 0) {
			return value;
		}
		int w = (W > items[i].w) ? items[i].w : W;
		value += w * (items[i].v + 0.0) / items[i].w;
		W -= w; 
	}
	
	return value;
}

int comparator(const void* i1, const void* i2) {
	
	Item* item1 = (Item*) i1;
	Item* item2 = (Item*) i2;
	double dens1 = (item1->v + 0.0) / item1->w;
	double dens2 = (item2->v + 0.0) / item2->w;
	
	if(dens2 < dens1) {
		return -1;
	} else if(dens2 > dens1) {
		return 1;
	}
	return 0;
}

void init_item(Item* item, int v, int w) {
	
	item->v = v;
	item->w = w;
}
