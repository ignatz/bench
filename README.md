A Small C++11 Benchmarking Library
==================================

Introduction
------------

Measurement is the basis for any thorough performance optimization.
This library provides an _as-easy-as-possible_ interface for benchmarking your
code.

	#include "bench/bench.h"
	
	// ...
	
	int x = 0;
	BENCH(TestBenchName,
		bench::preserve(x);
		x += 23;
	)
	
	BENCH(TestBenchName,
		bench::preserve(x);
		x *= 23;
	)
	
	// ...

In this example the benchmarked code is executed many times to get a better
measure. Furthermore, the number of iterations are estimated independently for
both tests such that the overall time consumed by one test is about 1 second
wall time. Therefore, the user himself doesn't need to guess a suitable amount
of iterations and if the code is rather time consuming only a single run is
carried out.

So how can we than compare the results? Easy, the framework normalizes all
results and provides relative measures regarding the first equally named test
bench. The result for our example looks something like:

	TestBenchName    1.54e+09 it/s        6.49e-10 s/it          100.00%
	TestBenchName    6.02e+08 it/s        1.66e-09 s/it          209.69%

By looking at the last column one can immediately see, that multiplications
consume about twice as much time as additions on my computer.

Contributing
------------
The library is rather small (approx. 130 SLOCs) and by using `C++11` lambdas
the amount of required preprocessor code is kept to a minimum. Feel free to to
play around.

License
-------
Copyright (c) 2012, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
Distributed under the terms of the GPLv2 or newer
