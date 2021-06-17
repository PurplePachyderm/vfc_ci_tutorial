#include <stdio.h>
#include <stdlib.h>
#include <time.h>


float naiveDotprod(float * x, float * y, size_t n) {
	float res = 0;

	for(size_t i=0; i<n; i++) {
		res += x[i] * y[i];
	}

	return res;
}


int main(void) {

	size_t n = 4096;
	float * x = malloc(n * sizeof(float));
	float * y = malloc(n * sizeof(float));

    srand(42);
	for(size_t i=0; i<n; i++) {
		x[i] = (float) rand() / RAND_MAX;
		y[i] = (float) rand() / RAND_MAX;
	}
	srand(time(NULL));

	float naiveRes = naiveDotprod(x, y, n);

	printf("Naive dotprod = %.7f \n", naiveRes);

	vfc_dump_probes(&probes);
	return 0;
}
