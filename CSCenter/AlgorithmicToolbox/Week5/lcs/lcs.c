#include <stdio.h>
#include <stdlib.h>

int lcs3(int *a, int n, int *b, int m, int *c, int l);
int max(int a, int b, int c);

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
	
	int m;
	if(scanf("%d", &m) != 1) {
		return 1;
	}
	
	int *b = malloc(sizeof(int) * m);
	for(int i = 0; i < m; i++) {
		if(scanf("%d", &b[i]) != 1) {
			return 1;
		}
	}
	
	int l;
	if(scanf("%d", &l) != 1) {
		return 1;
	}
	
	int *c = malloc(sizeof(int) * l);
	for(int i = 0; i < l; i++) {
		if(scanf("%d", &c[i]) != 1) {
			return 1;
		}
	}
	
	printf("%d\n", lcs3(a, n, b, m, c, l));
	
	free(a);
	free(b);
	free(c);
	return 0;
}

int lcs3(int *a, int n, int *b, int m, int *c, int l) {
	
	int *L = calloc((n+1)*(m+1)*(l+1), sizeof(int));
	#define L(i, j, k) L[(k)*((n+1)*(m+1)) + (i)*(m+1) + (j)]
	
	for(int k = 1; k <= l; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(a[i-1] == b[j-1] && b[j-1] == c[k-1]) {
					L(i, j, k) = L(i-1, j-1, k-1) + 1;
				} else {
					L(i, j, k) = max(L(i-1, j, k), L(i, j-1, k), L(i, j, k-1));
				}
			}
		}
	}
	
	int res = L(n, m, l);
	
	free(L);
	return res;
}

int max(int a, int b, int c) {
	
	int tmp = (a > b) ? a : b;
	return (tmp > c) ? tmp : c;
}
