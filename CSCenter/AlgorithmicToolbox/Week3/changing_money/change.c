#include <stdio.h>
#include <stdlib.h>

/* coins assumed to be sorted in reverse order
 * n is the number of coins
 * m is the input value for changing optimally
 * returns the optimal number of coins that changes m
 */
int optChange(int* coins, int n, int m) {

	int res = 0;
	for(int i = 0; i < n; i++) {
		if(m == 0) {
			break;
		}
		res += m / coins[i];
		m %= coins[i]; 
	}

	return res;
}

int main() {
	
	int m;
	if(scanf("%d", &m) != 1) {
		return 1;
	}
	
	int coins[] = {10, 5, 1};
 	int n = sizeof(coins) / sizeof(coins[0]);
	
	printf("%d\n", optChange(coins, n, m));
	
	return 0;
}
