#ifndef DP_OPEN_HPP_
#define DP_OPEN_HPP_

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
vector<size_t> dp_open(const vector< vec2<T> >& pts, size_t nVert)
{
	size_t nPts = pts.size();

	// precompute points to segments distances
	mat<T> dist = pts_seg_dist_sum_seq(pts);

	// initialize costs and previous pointers for single approximating segment
	mat<T> cost(nVert, nPts);
	mat<size_t> prev(nVert, nPts);
	dp_fill_first_row(nPts, dist, cost, prev);

	// compute all cost and previous pointers
	for (size_t i = 2; i < nVert; ++i)
	{
		for (size_t j = i; j <= nPts - nVert + i; ++j)
		{
			dp_fill_cell(nPts, dist, i, j, i - 1, j, cost, prev);
		}
	}

	// trace optimal approximation path
	vector<size_t> ind(nVert);
	ind[nVert - 1] = nPts - 1;
	for (size_t k = nVert - 1; k > 0; --k)
	{
		ind[k - 1] = prev(k, ind[k]);
	}

	DPRINTLN("DISTANCES:\n" << dist);
	DPRINTLN("COSTS:\n" << cost);
	DPRINTLN("PREVIOUS:\n" << prev);
	DPRINTLN("INDICES:\n" << ind);

	return ind;
}

#endif
