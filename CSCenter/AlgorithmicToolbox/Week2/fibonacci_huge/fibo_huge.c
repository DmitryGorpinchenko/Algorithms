#include <stdio.h>
#include <stdint.h>

uint64_t get_period_len(uint64_t m) {
	
	uint64_t period_len = 0;
	uint64_t prev1 = 0;
	uint64_t prev2 = 1;
	uint64_t res;
	do {
		res = (prev1 + prev2) % m;
		prev1 = prev2;
		prev2 = res;
		++period_len;
	} while(!(prev1 == 0 && prev2 == 1));
	
	return period_len;
}

uint64_t get_fibonacci_huge(uint64_t n, uint64_t m) {

	uint64_t period_len = get_period_len(m);
	uint64_t nth_fib_num_id = n % period_len;
	uint64_t prev1 = 0;
	uint64_t prev2 = 1;
	uint64_t res = n;
	for(uint64_t i = 2; i <= nth_fib_num_id; ++i) {
		res = (prev1 + prev2) % m;
		prev1 = prev2;
		prev2 = res;
	}
	
	return res;
}

int main() {
	
	uint64_t n, m;
	
	if(scanf("%llu %llu", &n, &m) != 2) {
		return 1;
	}

	printf("%llu\n", get_fibonacci_huge(n, m));
	
	return 0;
}
