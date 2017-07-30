#include <stdio.h>

int gcd_slow(int a, int b) {
	//write your code here
	int current_gcd = 1;
	for (int d = 2; d <= a && d <= b; d++) {
		if (a % d == 0 && b % d == 0) {
			if (d > current_gcd) {
				current_gcd = d;
			}
		}
	}
	return current_gcd;
}

int gcd(int a, int b) {
	
	if(b == 0) {
		return a;
	}	
	return gcd(b, a % b);
}

int main() {

	int a, b;	
	
	if(scanf("%d %d", &a, &b) != 2) {
		return 1;
	}
	
	printf("%d\n", gcd(a, b));

	return 0;
}

