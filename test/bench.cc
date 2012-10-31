#include "bench/bench.h"
int main(int argc, const char *argv[])
{

	int x = 0;

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
