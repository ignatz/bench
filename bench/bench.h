#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>

#ifndef BENCH_UNIT
#define BENCH_UNIT milliseconds
#endif

#define QUOTE(STR) " "#STR
#define TO_STRING(STR) QUOTE(STR)

namespace bench {
namespace detail {

template<typename Rep, typename Period>
inline
void msg(std::ostream& o, size_t iter, std::chrono::duration<Rep, Period> const& d)
{
	o <<    "N = " << std::setw(12) << iter
	  << "  dt = " << std::setw(10) << d.count()
	  << TO_STRING(BENCH_UNIT) << std::endl;
}

} // namespace detail
} // namespace bench

#define _BENCHN(N, SINK, ...) \
	{                                                                 \
		using namespace std::chrono;                                  \
		auto __t_start = system_clock::now();                         \
		for (size_t ITER = 0; ITER<N; ++ITER) { __VA_ARGS__ }         \
		auto __t_end = system_clock::now();                           \
		BENCH_UNIT __duration =                                       \
			duration_cast<BENCH_UNIT>(__t_end - __t_start);           \
		bench::detail::msg(SINK, N, __duration);                      \
	}

#define BENCHN(N, ...) _BENCHN(N, std::cout, __VA_ARGS__)
#define BENCH(...)      BENCHN(1, __VA_ARGS__)
