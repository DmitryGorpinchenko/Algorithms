#include <stdio.h>

int calc_fib(int n) {

	int prev1 = 0;
	int prev2 = 1;
	int res = n;
	for(int i = 2; i <= n; i++) {
		res = prev1 + prev2;
		prev1 = prev2;
		prev2 = res;
	}
	return res;
}

int main() {

	int n = 0;
	
	if(scanf("%d", &n) != 1) {
		return 1;
	}
	
	printf("%d\n", calc_fib(n));
	
	return 0;
}

