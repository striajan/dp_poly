#ifndef DP_OPEN_HPP_
#define DP_OPEN_HPP_

#include <iostream>
#include <limits>
#include <vector>
#include "debug.hpp"
#include "distance.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

using std::vector;

template <typename T>
vector<size_t> dp_open(const vector< vec2<T> >& pts, const size_t nVert)
{
	size_t nPts = pts.size();

	mat<T> dist(nPts, nPts);
	vector<T> distBuff(nPts);
	mat<T> cost(nVert, nPts);
	mat<size_t> prev(nVert, nPts);
	vector<size_t> ind(nVert);

	// precompute points to segments distances
	for (size_t j = 0; j < nPts; ++j)
	{
		for (size_t k = j; k < nPts; ++k)
		{
			dist(j, k) = pts_seg_dist_sum(pts, j, k, distBuff);
		}
	}

	// initialize costs and previous pointers for single approximating segment
	for (size_t j = 1; j < (nPts - nVert + 2); ++j)
	{
		cost(1, j) = dist(0, j);
		prev(1, j) = 0;
	}

	// compute all cost and previous pointers
	for (size_t i = 2; i < nVert; ++i)
	{
		for (size_t j = i; j <= nPts - nVert + i; ++j)
		{
			cost(i, j) = std::numeric_limits<T>::max();
			for (size_t k = i - 1; k < j; ++k)
			{
				T c = cost(i - 1, k) + dist(k, j);
				if (c < cost(i, j))
				{
					cost(i, j) = c;
					prev(i, j) = k;
				}
			}
		}
	}

	// trace optimal approximation path
	ind[nVert - 1] = nPts - 1;
	for (size_t k = nVert - 1; k > 0; --k)
	{
		ind[k - 1] = prev(k, ind[k]);
	}

	DPRINTLN("DISTANCES:\n" << dist);
	DPRINTLN("COSTS:\n" << cost);
	DPRINTLN("PREVIOUS POINTERS:\n" << prev);
	DPRINTLN("TRACED INDICES:\n" << ind);

	return ind;
}

#endif
