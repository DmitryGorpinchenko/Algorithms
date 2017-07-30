#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 101

int edit_distance(char *str1, int len1, char *str2, int len2);
int min(int a, int b, int c);

int main() {
	
	char *str1 = malloc(sizeof(char) * MAX_LENGTH);
	char *str2 = malloc(sizeof(char) * MAX_LENGTH);
	if(scanf("%s%s", str1, str2) != 2) {
		return 1;
	}
	
	printf("%d\n", edit_distance(str1, strlen(str1), str2, strlen(str2)));
	
	free(str1);
	free(str2);
	return 0;
}

int edit_distance(char *str1, int n, char *str2, int m) {
	
	int *D = malloc(sizeof(int) * (n + 1) * (m + 1));
	
	for(int i = 0; i < n + 1; i++) {
		D[i * (m + 1)] = i;
	}
	for(int j = 0; j < m + 1; j++) {
		D[j] = j;
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			int insertion = D[i * (m + 1) + j - 1] + 1;
			int deletion = D[(i - 1) * (m + 1) + j] + 1;
			int match = D[(i - 1) * (m + 1) + j - 1];
			int mismatch = D[(i - 1) * (m + 1) + j - 1] + 1;
			if(str1[i-1] == str2[j-1]) {
				D[i * (m + 1) + j] = min(insertion, deletion, match);
			} else {
				D[i * (m + 1) + j] = min(insertion, deletion, mismatch);
			}
		}
	}
	
	int dist = D[n*(m+1) + m];
	
	free(D);
	return dist;
}

int min(int a, int b, int c) {
	
	int tmp = a < b ? a : b;
	return c < tmp ? c : tmp;
}
