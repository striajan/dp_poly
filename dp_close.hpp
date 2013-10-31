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
vector<size_t> dp_close(const vector< vec2<T> >& pts, const size_t nVert)
{
	size_t nPts = pts.size();

	// precompute points to segments distances
	mat<T> dist = pts_seg_dist_sum_cyc(pts);

	mat<T> cost(nVert, nPts);
	mat<size_t> prev(nVert, nPts);
	vector<size_t> ind(nVert);

	DPRINTLN("DISTANCES:\n" << dist);
	DPRINTLN("COSTS:\n" << cost);
	DPRINTLN("PREVIOUS POINTERS:\n" << prev);
	DPRINTLN("TRACED INDICES:\n" << ind);

	return ind;
}

#endif
