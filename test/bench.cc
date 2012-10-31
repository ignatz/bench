#include "bench/bench.h"
#include <cmath>

int main(int argc, const char *argv[])
{

	int x = 0;

	BENCH(SomeName,
		x += 23;
		bench::preserve(x);
	)

	BENCH(SomeName,
		x *= 23;
		bench::preserve(x);
	)

	BENCH(SomeName,
		x /= 23;
		bench::preserve(x);
	)

	BENCH(SomeName,
		x += sqrt(23);
		bench::preserve(x);
	)

	return 0;
}
