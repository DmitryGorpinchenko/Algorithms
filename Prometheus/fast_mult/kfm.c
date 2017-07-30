#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT_SIZE 10000

void mul(const char *num_l, const char *num_r, char *prod);

int main()
{
	//const char *num_l = "21625695688898558125310188636840316594920403182768";
	//const char *num_r = "13306827740879180856696800391510469038934180115260";
	//const char *num_l = "1685287499328328297814655639278583667919355849391453456921116729";
	//const char *num_r = "0";
	const char *num_l = "1685287499328328297814655639278583667919355849391453456921116729";
	const char *num_r = "7114192848577754587969744626558571536728983167954552999895348492";
	
	char *prod = (char *) malloc(sizeof(char) * MAX_PRODUCT_SIZE);
	
	mul(num_l, num_r, prod);
	
	printf("%s\n", prod);

	free(prod);
	return 0;
}

void mul(const char *num_l, const char *num_r, char *prod)
{
	static char mul_res[MAX_PRODUCT_SIZE]; 
	static char tmp_res[MAX_PRODUCT_SIZE]; 
	
	int    i, j, k, c;
	size_t l_sz, r_sz;
	
	if ((l_sz = strlen(num_l)) == 0 
	 || (r_sz = strlen(num_r)) == 0) {
		
		return;
	}
	
	memset(mul_res, 0, MAX_PRODUCT_SIZE);
	memset(tmp_res, 0, MAX_PRODUCT_SIZE);
	
	for (i = r_sz - 1; i >= 0; i--) {
		int sf = r_sz - 1 - i;
		int dr = num_r[i] - '0';
		
		k = 0;
		c = 0;
		for (j = l_sz - 1; j >= 0; j--) {
			int dl = num_l[j] - '0';
			int dp = dl * dr + c;
		
			tmp_res[k++] = dp % 10;
			c = dp / 10;
		}
		tmp_res[k] = c;
		
		c = 0;
		for (j = 0; j <= k; j++) {
			int dl = tmp_res[j];
			int dr = mul_res[j + sf];	
			int da = (dl + dr) + c;
			
			mul_res[j + sf] = da % 10;
			c = da / 10;
		}
	}
	
	i = 0;
	j = MAX_PRODUCT_SIZE;
	while (j > 1 && !mul_res[j - 1]) {
		j--;
	}
	while (j > 0 && (prod[i++] = mul_res[--j] + '0'))
		;
	prod[i] = 0;	
}
