#ifndef DP_COMMON_HPP_
#define DP_COMMON_HPP_

#include <algorithm>
#include <limits>
#include <vector>
#include "debug.hpp"
#include "distance.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

template <typename T>
void dp_fill_dist_row(const size_t nPts, const size_t nVert, const mat<T>& dist,
		mat<T>& cost, mat<size_t>& prev)
{
	for (size_t j = 1; j <= nPts - nVert + 1; ++j)
	{
		cost(1, j) = dist(0, j);
		prev(1, j) = 0;
	}
}

template <typename T>
void dp_fill_cell(const size_t nPts, const mat<T>& dist,
		const size_t i, const size_t j, const size_t k1, const size_t k2,
		mat<T>& cost, mat<size_t>& prev)
{
	T cmin = std::numeric_limits<T>::max();
	size_t kmin = 0;

	for (size_t k = k1; k <= k2; ++k)
	{
		const T c = cost(i - 1, k) + dist(k % nPts, j % nPts);
		if (c < cmin)
		{
			cmin = c;
			kmin = k;
		}
	}

	cost(i, j) = cmin;
	prev(i, j) = kmin;
}

std::vector<size_t> dp_trace_path(const size_t nPts, const size_t nVert,
		const size_t i, const size_t j, const mat<size_t>& prev)
{
	vector<size_t> ind(nVert);

	// index of vertex 'p' can go over 'nPts' so we have to modulo
	size_t p = j;
	ind[nVert - 1] = j % nPts;

	// trace path
	for (size_t r = 0; r < nVert - 1; ++r)
	{
		p = prev(i - r, p);
		ind[nVert - 2 - r] = p % nPts;
	}

	// rotate indices so that the least one goes first
	std::vector<size_t>::iterator it = std::min_element(ind.begin(), ind.end());
	std::rotate(ind.begin(), it, ind.end());

	return ind;
}

#endif
