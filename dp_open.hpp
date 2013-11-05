#ifndef DP_OPEN_HPP_
#define DP_OPEN_HPP_

#include <vector>
#include "debug.hpp"
#include "distance.hpp"
#include "dp_common.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

using std::vector;

template <typename T>
vector<size_t> dp_open(const vector< vec2<T> >& pts, const size_t nVert)
{
	const size_t nPts = pts.size();

	// precompute points to segments distances
	const mat<T> dist = pts_seg_dist_sum_seq(pts);

	// initialize costs and previous pointers for single approximating segment
	mat<T> cost(nVert, nPts);
	mat<size_t> prev(nVert, nPts);
	dp_fill_dist_row(nPts, nVert, dist, cost, prev);

	// compute all cost and previous pointers
	for (size_t i = 2; i < nVert; ++i)
	{
		for (size_t j = i; j <= nPts - nVert + i; ++j)
		{
			const size_t k1 = i - 1;
			const size_t k2 = j - 1;
			dp_fill_cell(nPts, dist, i, j, k1, k2, cost, prev);
		}
	}

	// trace the optimal path
	const vector<size_t> ind = dp_trace_path(nPts, nVert, nVert - 1, nPts - 1, prev);

//	DPRINTLN("DISTANCES:\n" << dist);
//	DPRINTLN("COSTS:\n" << cost);
//	DPRINTLN("PREVIOUS:\n" << prev);
	DPRINTLN("INDICES:\n" << ind);

	return ind;
}

#endif
