# A Small C++11 Benchmark Library

## Usage
Measurement is the foundation for any thorough performance optimization.
`bench` tries to make benchmarking _as-easy-as-possible_.

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

In this example we have two small test benches. Note, that neither a single
addition nor multiplication takes long enough to get reliable measurements.
Therefore, we need to average over multiple runs. In fact, `bench` does this
already for us. After an initial trial the number of iterations necessary to
reach an overall runtime of *1s* is estimated. That's nice, because otherwise
we would have to guess at least how many iterations are necessary for the
measurement and how many are reasonable considering the overall execution time.

Sometimes, this behaviour is inadequate, if for example some internal *state*
keeps us from iterating or if the time consumed per iteration varies a lot.
Then the `BENCH_N(<name>, <N>, <code>)` macro can be used to specify the number
of iterations.

## Results
So how can we compare the results if all measurements are targeted at *1s*?
Easy, all results are normalized relative measures are provided. All
equally named test benches are compared against the first one.

The output for the example above looks something like (DefaultLayout):

	TestBenchName    1.54e+09 it/s        6.49e-10 s/it          100.00%
	TestBenchName    6.02e+08 it/s        1.66e-09 s/it          209.69%

By looking at the last column we can instantly see, that on this machine
multiplications take approximately twice as long as additions.

## Layout
Beyond measuring once, it can be useful to monitor the development of your
programs performance. Customizable layouts make the results easily accessible
for plotting and websites. `bench` currently ships with the `DefaultLayout` and
a `CSVLayout`.


## License
Copyright 2013, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)

bench is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

bench is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with bench.  If not, see <http://www.gnu.org/licenses/>.
