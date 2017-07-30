#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LEN 30

typedef struct {
	int n_ops;
	int n_dig;
	int *digits;
	char *ops;
	int64_t *m;
	int64_t *M;
	
	#define M(e, i, j) e->M[(i) * (e->n_dig) + (j)]
	#define m(e, i, j) e->m[(i) * (e->n_dig) + (j)]
} expr;

void init_expr(expr *e, char *expr_str);
void free_expr(expr *e);
int64_t expr_max_value(expr *e);
void min_and_max(expr *e, int i, int j);

int64_t calc(int64_t op1, int64_t op2, char op);
int64_t minimum(int64_t a, int64_t b, int64_t c, int64_t d, int64_t e);
int64_t maximum(int64_t a, int64_t b, int64_t c, int64_t d, int64_t e);

int main() {
	
	char *expr_str = malloc(sizeof(char) * MAX_LEN);
	if(scanf("%s", expr_str) != 1) {
		return 1;
	}
	
	expr *e = malloc(sizeof(expr));
	init_expr(e, expr_str);
	
	printf("%lld\n", expr_max_value(e));
	
	free(expr_str);
	free_expr(e);
	return 0;
}

int64_t expr_max_value(expr *e) {
	
	int n = e->n_dig;
	for(int i = 0; i < n; i++) {
		m(e, i, i) = e->digits[i];
		M(e, i, i) = e->digits[i];
	}
	
	for(int s = 1; s <= e->n_ops; s++) {
		for(int i = 0; i < n - s; i++) {
			int j = i + s;
			min_and_max(e, i, j);
		}
	}
	
	return M(e, 0, e->n_dig - 1);
}

void min_and_max(expr *e, int i, int j) {
	
	int64_t min = INT64_MAX;
	int64_t max = INT64_MIN;
	
	for(int k = i; k < j; k++) {
		int64_t a = calc(M(e, i, k), M(e, k + 1, j), e->ops[k]);
		int64_t b = calc(M(e, i, k), m(e, k + 1, j), e->ops[k]);
		int64_t c = calc(m(e, i, k), M(e, k + 1, j), e->ops[k]);
		int64_t d = calc(m(e, i, k), m(e, k + 1, j), e->ops[k]);
		min = minimum(min, a, b, c, d);
		max = maximum(max, a, b, c, d);
	}
	
	m(e, i, j) = min;
	M(e, i, j) = max;
}

int64_t calc(int64_t op1, int64_t op2, char op) {
	
	int64_t res;
	
	if(op == '+') {
		res = op1 + op2;
	} else if(op == '-') {
		res = op1 - op2;
	} else if(op == '*') {
		res = op1 * op2;
	}
	
	return res;
}

int64_t minimum(int64_t a, int64_t b, int64_t c, int64_t d, int64_t e) {
	
	int64_t tmp1 = a < b ? a : b;
	int64_t tmp2 = c < d ? c : d;
	int64_t tmp3 = tmp1 < tmp2 ? tmp1 : tmp2;
	return tmp3 < e ? tmp3 : e;
}

int64_t maximum(int64_t a, int64_t b, int64_t c, int64_t d, int64_t e) {

	int64_t tmp1 = a > b ? a : b;
	int64_t tmp2 = c > d ? c : d;
	int64_t tmp3 = tmp1 > tmp2 ? tmp1 : tmp2;
	return tmp3 > e ? tmp3 : e;
}

void init_expr(expr *e, char *expr_str) {
	
	int len = strlen(expr_str);
	int n = (len - 1) / 2;
	e->n_ops = n;
	e->n_dig = n + 1;
	e->ops = malloc(sizeof(char) * e->n_ops);
	e->digits = malloc(sizeof(int) * e->n_dig);
	e->m = calloc(e->n_dig * e->n_dig, sizeof(int64_t));
	e->M = calloc(e->n_dig * e->n_dig, sizeof(int64_t));
	
	for(int i = 0, j = 0; i < len; i += 2, j++) {
		e->digits[j] = expr_str[i] - '0';
	}
	for(int i = 1, j = 0; i < len; i += 2, j++) {
		e->ops[j] = expr_str[i];
	}
}

void free_expr(expr *e) {
	
	free(e->digits);
	free(e->ops);
	free(e->m);
	free(e->M);
	free(e);
}
