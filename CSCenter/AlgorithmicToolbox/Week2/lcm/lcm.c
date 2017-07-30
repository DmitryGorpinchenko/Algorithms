#include <stdio.h>
#include <stdint.h>

int gcd(int a, int b) {
	
	if(b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

uint64_t lcm(int a, int b) {
  
	return ((uint64_t) a) * b / gcd(a, b);
}

int main() {
  
	int a, b;

	if(scanf("%d %d", &a, &b) != 2) {
		return 1;
	}
	
	printf("%llu\n", lcm(a, b));
	
	return 0;
}

