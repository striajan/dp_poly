#ifndef DP_CLOSE_HPP_
#define DP_CLOSE_HPP_

#include <limits>
#include <vector>
#include "debug.hpp"
#include "distance.hpp"
#include "dp_common.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

using std::vector;

template <typename T>
vector<size_t> dp_close(const vector< vec2<T> >& pts, const size_t nVert)
{
	const size_t nPts = pts.size();

	// precompute points to segments distances
	const mat<T> dist = pts_seg_dist_sum_cyc(pts);

	// initialize costs and previous pointers for single approximating segment
	mat<T> cost(2 * nVert + 1, 2 * nPts + 1, -1);
	mat<size_t> prev(2 * nVert + 1, 2 * nPts + 1, 9999);
	dp_fill_dist_row(nPts, nVert, dist, cost, prev);

	// first cycle (i = 2..nVert)
	for (size_t i = 2; i <= nVert; ++i)
	{
		for (size_t j = i; j <= nPts - nVert + i; ++j)
		{
			const size_t k1 = i - 1;
			const size_t k2 = j - 1;
			dp_fill_cell(nPts, dist, i, j, k1, k2, cost, prev);
		}
	}

	// long row (i = nVert)
	for (size_t j = nPts + 1; j < 2 * nPts - nVert + 1; ++j)
	{
		const size_t k1 = std::max(nVert - 1, j - nPts + 1);
		const size_t k2 = nPts - 1;
		dp_fill_cell(nPts, dist, nVert, j, k1, k2, cost, prev);
	}

	// row above long row (i = nVert+1)
	for (size_t j = nPts + 1; j < 2 * nPts - nVert + 2; ++j)
	{
		const size_t k1 = std::max(nVert, j - nPts + 1);
		const size_t k2 = j - 1;
		dp_fill_cell(nPts, dist, nVert + 1, j, k1, k2, cost, prev);
	}

	// second cycle (i = nVert+2..2*nVert)
	for (size_t i = nVert + 2; i <= 2 * nVert; ++i)
	{
		for (size_t j = i - nVert + nPts; j <= 2 * nPts - 2 * nVert + i; ++j)
		{
			const size_t k1 = i - nVert + nPts - 1;
			const size_t k2 = j - 1;
			dp_fill_cell(nPts, dist, i, j, k1, k2, cost, prev);
		}
	}

	size_t cmin = std::numeric_limits<T>::max();
	size_t imin = nVert;
	size_t jmin = nPts;

	size_t testedPairs = 0;
	size_t conjugPairs = 0;

	// select conjugate end point
	for (size_t i = nVert; i <= 2 * nVert; ++i)
	{
		for (size_t j = i - nVert + nPts; j <= 2 * nPts - 2 * nVert + i; ++j)
		{
			size_t p = j;
			for (size_t k = 0; k < nVert; ++k)
			{
				p = prev(i - k, p);
			}

			if (p == i - nVert)
			{
				const T c = cost(i, j) - cost(i - nVert, p);
				if (c < cmin)
				{
					cmin = c;
					imin = i;
					jmin = j;
				}

				++conjugPairs;
			}

			++testedPairs;
		}
	}

	DPRINTLN(conjugPairs << " / " << testedPairs);

	// trace the optimal path
	const vector<size_t> ind = dp_trace_path(nPts, nVert, imin, jmin, prev);

//	DPRINTLN("DISTANCES:\n" << dist);
//	DPRINTLN("COSTS:\n" << cost);
//	DPRINTLN("PREVIOUS:\n" << prev);
	DPRINTLN("INDICES:\n" << ind);

	return ind;
}

#endif
