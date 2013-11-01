#ifndef DP_CLOSE_HPP_
#define DP_CLOSE_HPP_

#include <limits>
#include <vector>
#include "debug.hpp"
#include "distance.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

using std::vector;

template <typename T>
vector<size_t> dp_close(const vector< vec2<T> >& pts, size_t nVert)
{
	size_t nPts = pts.size();

	// precompute points to segments distances
	mat<T> dist = pts_seg_dist_sum_cyc(pts);

	DPRINTLN("DISTANCES:\n" << dist);

	// initialize costs and previous pointers for single approximating segment
	mat<T> cost(2 * nVert, 2 * nPts, -1);
	mat<size_t> prev(2 * nVert, 2 * nPts, 99);
	dp_fill_first_row(nPts, dist, cost, prev);

	DPRINTLN("FIRST:");

	// standard computation
	for (size_t i = 2; i <= nVert; ++i)
	{
		for (size_t j = i; j <= nPts - nVert + i; ++j)
		{
			size_t k1 = i - 1;
			size_t k2 = j;
			dp_fill_cell(nPts, dist, i, j, k1, k2, cost, prev);
		}
	}

	DPRINTLN("\nLONG:");

	// long row computation
	for (size_t j = nPts + 1; j < 2 * nPts - nVert; ++j)
	{
		size_t k1 = (j - nPts) + nVert - 1;
		size_t k2 = nPts;
		dp_fill_cell(nPts, dist, nVert, j, k1, k2, cost, prev);
	}

//	DPRINTLN("\nSECOND:");
//
//	// second cycle computation
//	for (size_t i = nVert + 1; i < 2 * nVert; ++i)
//	{
//		for (size_t j = i; j <= 2 * (nPts - nVert) + i; ++j)
//		{
//			dp_fill_cell(nPts, dist, i, j, i - 1, j, cost, prev);
//		}
//	}

	DPRINTLN("\nCOSTS:\n" << cost);
	DPRINTLN("PREVIOUS:\n" << prev);

	vector<size_t> ind(nVert);
	return ind;
}

#endif
