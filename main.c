#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vfc_probes.h>


float naiveDotprod(float * x, float * y, size_t n) {
	float res = 0;

	for(size_t i=0; i<n; i++) {
		res += x[i] * y[i];
	}

	return res;
}


float recursiveDotprod(float * x, float * y, size_t n) {

	// NOTE This implementation assumes that n can be written as 2^k
	if((n & (n - 1)) != 0) {
		return 0;
	}

	// Base case
	if(n == 1) {
		return x[0] * y[0];
	}

	// Recursive case
	else {
		// Split arrays in 2 and do a recursive call for each half
		return recursiveDotprod(x, y, n / 2) +
			recursiveDotprod(&(x[n/2]), &(y[n/2]), n / 2);
	}
}


int main(void) {
	vfc_probes probes = vfc_init_probes();

	srand(42);
	size_t n = 4096;
	float * x = malloc(n * sizeof(float));
	float * y = malloc(n * sizeof(float));

	for(size_t i=0; i<n; i++) {
		x[i] = (float) rand() / RAND_MAX;
		y[i] = (float) rand() / RAND_MAX;
	}
	srand(time(NULL));

	float naiveRes = naiveDotprod(x, y, n);
	vfc_probe(&probes, "dotprod_test", "naive", naiveRes);

	float recursiveRes = recursiveDotprod(x, y, n);
	vfc_probe(&probes, "dotprod_test", "recursive", recursiveRes);

	printf("Naive dotprod = %.12f \n", naiveRes);
	printf("Recursive dotprod = %.12f \n", recursiveRes);

	vfc_dump_probes(&probes);

	return 0;
}
