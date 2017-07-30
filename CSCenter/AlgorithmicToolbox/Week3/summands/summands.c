#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_LEN 10000

int* opt_summands(int n, int* k);

int main() {
	
	int n;
	if(scanf("%d", &n) != 1) {
		return 1;
	}
	
	int k;
	int *summands = opt_summands(n, &k);
	
	printf("%d\n", k);
	for(int i = 0; i < k; i++) {
		printf("%d ", summands[i]);
	}
	printf("\n");
	
	free(summands);
	return 0;
}

int* opt_summands(int n, int* k) {
	
	*k = 0;
	int curr_len = DEFAULT_LEN;
	int *summands = malloc(sizeof(int) * curr_len);
	
	int m = n;
	int l = 1;
	while(m > 2 * l) {
		summands[(*k)++] = l;
		m -= l;
		l++;
		if(*k >= curr_len) {
			curr_len *= 2;
			summands = realloc(summands, sizeof(int) * curr_len);
		}
	}
	summands[(*k)++] = m;
	
	return summands;
}
