#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>
#include <string>

#ifndef BENCH_UNIT
#define BENCH_UNIT milliseconds
#endif

#define QUOTE(STR) #STR
#define TO_STRING(STR) QUOTE(STR)

#define BENCH_CLOCK  std::chrono::system_clock

#define BENCH_DT(TIME)                                    \
	std::chrono::duration_cast<std::chrono::BENCH_UNIT>(  \
		BENCH_CLOCK::now() - TIME)


namespace bench {

using namespace std::chrono;

struct reference_time
{
	static std::map<std::string, double>& get()
	{
		static std::map<std::string, double> _m;
		return _m;
	}
};

namespace detail {

template<typename Rep, typename Period>
inline
void msg(std::string s, size_t iter,
	duration<Rep, Period> const& d)
{
	double f = double(iter)/duration_cast<nanoseconds>(d).count()*pow(10,9);
	double r = f;
	typename std::map<std::string, double>::iterator it;
	if ((it = reference_time::get().find(s)) != reference_time::get().end())
		r = it->second;
	else
		reference_time::get()[s] = f;

	using namespace std;
	cout.precision(2);
	cout << setw(12) << scientific << f   << " it/s    "
	     << setw(12) << scientific << 1/f << " s/it    "
	     << setw(12) << fixed << r/f * 100 << "%"
		 << std::endl;
}

} // namespace detail

template <class T>
void preserve(T&& val)
{
	  asm volatile("" : "+r" (val));
}

} // namespace bench


#define BENCH_THRESH std::chrono::seconds(1)

#define TEST(NAME, ...) \
{                                                                     \
	size_t ITER = 0;                                                  \
	auto __t   = BENCH_CLOCK::now();                                  \
	__VA_ARGS__                                                       \
	auto __d   = BENCH_DT(__t);                                       \
	size_t END = BENCH_THRESH /                                       \
		(__d.count() ? __d : std::chrono::nanoseconds(1));            \
	for (; ITER < END; ITER++) { __VA_ARGS__ }                        \
	__d = BENCH_DT(__t);                                              \
	bench::detail::msg(TO_STRING(NAME), END+1, __d);                  \
}
