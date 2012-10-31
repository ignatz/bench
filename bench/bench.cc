#include "bench/bench.h"

#include <iostream>
#include <iomanip>
#include <map>

namespace bench {
namespace detail {

double reference_time(
	std::string const& name,
	double const measured_frequency)
{
	typedef std::map<std::string, double> type;
	static type _m;

	type::iterator it;
	if ((it = _m.find(name)) != _m.end())
		return it->second;

	_m[name] = measured_frequency;
	return measured_frequency;
}

void message(
	std::string const& name,
	size_t const iterations,
	BENCH_DURATION const duration)
{
	double frequency = duration_to_frequency(iterations, duration);
	double reference = reference_time(name, frequency);

	using namespace std;
	cout.precision(2);
	cout << setw(12) << scientific << frequency   << " it/s    "
	     << setw(12) << scientific << 1/frequency << " s/it    "
	     << setw(12) << fixed << reference/frequency * 100 << "%"
		 << std::endl;
}

} // namespace detail
} // namespace bench
