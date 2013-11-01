#ifndef DP_COMMON_HPP_
#define DP_COMMON_HPP_

#include <limits>
#include <vector>
#include "debug.hpp"
#include "distance.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

template <typename T>
void dp_fill_first_row(size_t nPts, const mat<T>& dist,
		mat<T>& cost, mat<size_t>& prev)
{
	for (size_t j = 1; j < nPts; ++j)
	{
		cost(1, j) = dist(0, j);
		prev(1, j) = 0;
	}
}

template <typename T>
void dp_fill_cell(size_t nPts, const mat<T>& dist,
		size_t i, size_t j, size_t k1, size_t k2,
		mat<T>& cost, mat<size_t>& prev)
{
	T cmin = std::numeric_limits<T>::max();
	size_t kmin = 0;

	for (size_t k = k1; k < k2; ++k)
	{
		T c = cost(i - 1, k) + dist(k % nPts, j % nPts);
		if (c < cmin)
		{
			cmin = c;
			kmin = k;
		}
	}

	cost(i, j) = cmin;
	prev(i, j) = kmin;

	DPRINTLN("[" << i << "," << j << "]: " << k1 << ".." << k2 - 1 << ", " << kmin << ", " << cmin);
}

#endif
