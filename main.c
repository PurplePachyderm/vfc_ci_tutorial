#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vfc_probes.h>
#define N 4096

float recursiveDotprod(float * x, float * y, size_t n) {
	// NOTE This implementation assumes that N can be written as 2^k
	if((n & (n - 1)) != 0) {
		return 0;
	}

	// Base case
	if(n == 1) {
		return x[0] * y[0];
	}

	// Recursive case
	else {
		// Split array in 2 and do a recursive call for each half
		return recursiveDotprod(x, y, n / 2) +
			recursiveDotprod(&(x[n/2]), &(y[n/2]), n / 2);
	}
}


float naiveDotprod(float * x, float * y, size_t n) {
	float res = 0;

	for(size_t i=0; i<n; i++) {
		res += x[i] * y[i];
	}

	return res;
}


int main(void) {
	vfc_probes probes = vfc_init_probes();
	float x [N], y [N];

	srand(42);
	for(size_t i=0; i<N; i++) {
		x[i] = rand() / (float) RAND_MAX;
		y[i] = rand() / (float) RAND_MAX;
	}
	srand(time(NULL));

	float naiveRes = naiveDotprod(x, y, N);
	vfc_probe(&probes, "dotprod_test", "naive", naiveRes);

	float recursiveRes = recursiveDotprod(x, y, N);
                vfc_probe(&probes, "dotprod_test", "recursive", recursiveRes);
	printf("Naive dotprod = %.7f \n", naiveRes);

         vfc_dump_probes(&probes);
	return 0;
}
