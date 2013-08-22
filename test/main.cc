#include <bench/bench.h>
#include <cmath>
#include <chrono>
#include <thread>

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

	BENCH(TestBenchName,
		std::chrono::seconds d(5);
		std::this_thread::sleep_for(d);
	)

	BENCH_N(TestBenchName, 1,
		std::chrono::seconds d(1);
		std::this_thread::sleep_for(d);
	)

	bench::run("SomeOtherName",
			   []() {
					std::chrono::milliseconds d(1337);
					std::this_thread::sleep_for(d);
			   },
			   bench::CSVLayout());

	return 0;
}
