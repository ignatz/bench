#include "bench/bench.h"
#include <cmath>

int main(int, char const**)
{

	int x = 0;

	BENCH(TestBenchName,
		bench::preserve(x);
		x += 23;
	)

	BENCH(TestBenchName,
		bench::preserve(x);
		x *= 23;
	)

	BENCH(TestBenchName,
		bench::preserve(x);
		x /= 23;
	)

	BENCH(TestBenchName,
		bench::preserve(x);
		x += sqrt(23);
	)

	return 0;
}
