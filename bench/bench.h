#pragma once

// Copyright (c) 2012, Sebastian Jeltsch (sjeltsch@kip.uni-heidelberg.de)
// Distributed under the terms of the GPLv2 or newer

#include <chrono>
#include <string>

#include <iostream>
#include <iomanip>
#include <map>

namespace bench {

using namespace std::chrono;

// some defines
typedef steady_clock      clock;
typedef time_point<clock> time_t;
typedef nanoseconds       duration;

// iterate test until `thresh` time has passed
static seconds const thresh = seconds(1);

inline
double find_or_store_reference(
	std::string const& name,
	double const frequency)
{
	typedef std::map<std::string, double> type;
	static type _m;

	type::iterator it;
	if ((it = _m.find(name)) != _m.end())
		return it->second;

	_m[name] = frequency;
	return frequency;
}

namespace detail {

inline
double to_frequency(
	size_t const iterations,
	duration const duration)
{
	return double(iterations) / duration_cast<nanoseconds>(duration).count() *
		nanoseconds::period::den;
}

inline
duration delta_t(time_t const& t)
{
	return duration_cast<duration>(clock::now() - t);
}

inline
size_t iterations(duration const& d)
{
	size_t iter = thresh / (d.count() ? d : nanoseconds(1));
	return iter ? iter : 1;
}

} // namespace detail

struct DefaultLayout
{
	DefaultLayout(std::ostream& os = std::cout) : _os(os) {}

	void operator() (std::string const& name,
					 double const frequency) const
	{
		static size_t const spacing = 12;

		double const reference = find_or_store_reference(name, frequency);

		_os << std::setw(spacing) << std::left << name << std::right;
		_os.precision(2);
		_os << std::setw(spacing) << std::scientific << frequency   << " it/s    "
		    << std::setw(spacing) << std::scientific << 1/frequency << " s/it    "
		    << std::setw(spacing) << std::fixed << reference/frequency * 100 << "%"
		    << std::endl;
	}

private:
	std::ostream& _os;
};

struct CSVLayout
{
	CSVLayout(std::ostream& os = std::cout) : _os(os) {}

	void operator() (std::string const& name,
					 double const frequency) const
	{
		double const reference = find_or_store_reference(name, frequency);

		_os << "# name, it/s, s/it, %" << std::endl;
		_os << name << ", "
		    << std::scientific << frequency   << ", "
		    << std::scientific << 1/frequency << ", "
		    << std::fixed << reference/frequency * 100 << std::endl;
	}

private:
	std::ostream& _os;
};

template <class T>
inline
void preserve(T&& val)
{
	  asm volatile("" : "+r" (val));
}

template<typename Lambda, typename Layout>
void run(
	std::string const& name,
	Lambda const& code,
	Layout const& layout = DefaultLayout(),
	size_t const iterations = 1,
	size_t const offset = 0,
	time_t const time = clock::now())
{
	for (size_t ii = offset; ii < iterations ; ++ii)
		code();

	double frequency = detail::to_frequency(iterations, detail::delta_t(time));
	layout(name, frequency);
}

} // namespace bench

#define BENCH_L(NAME, LAYOUT, ...) \
{ \
	auto __lambda = [&](){ __VA_ARGS__ }; \
	auto __t = bench::clock::now(); \
	__lambda(); \
	auto __d = bench::detail::delta_t(__t); \
	size_t __i = bench::detail::iterations(__d); \
	bench::run( #NAME , __lambda, LAYOUT, __i, 1, __t); \
}

#define BENCH(NAME, ...) \
	BENCH_L(NAME, bench::DefaultLayout(), __VA_ARGS__)

#define BENCH_NL(NAME, N, LAYOUT, ...) \
{ \
	auto __lambda = [&](){ __VA_ARGS__ }; \
	bench::run( #NAME , __lambda, LAYOUT, N); \
}

#define BENCH_N(NAME, N, ...) \
	BENCH_NL(NAME, N, bench::DefaultLayout(), __VA_ARGS__)
