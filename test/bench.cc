#include "bench/bench.h"
int main(int argc, const char *argv[])
{

	int x = 0;
	//BENCH(
		//for (unsigned long ii = 0; ii < 1000000000; ++ii)
			//x +=ii;
	//)

	//x = 0;
	//BENCHN(1000000000,
		//x += ITER;
	//)


	TEST(Kocky,
		x += 23;
		bench::preserve(x);
	)

	TEST(Kocky,
		x *= 23;
		bench::preserve(x);
	)

	TEST(Kocky,
		x /= 23;
		bench::preserve(x);
	)

	TEST(Kocky,
		x += sqrt(23);
		bench::preserve(x);
	)

	return 0;
}
