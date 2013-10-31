#ifndef DP_POLY_HPP_
#define DP_POLY_HPP_

#include <iostream>
#include <limits>
#include <vector>
#include "debug.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

using std::vector;

template <typename T>
void pts_seg_dist(const vector< vec2<T> >& pts, const size_t i, const size_t j, vector<T>& dist)
{
	if (j - i >= 0)
	{
		// first point "i" of the segment
		const vec2<T>& pi = pts[i];

		// vector u connecting first point "i" with last "j"
		vec2<T> u = pts[j] - pts[i];
		T un2 = u.norm2();

		// compute distances to all inner points
		for (size_t k = i + 1; k < j; ++k)
		{
			// vector v connecting first point "i" with point "k"
			vec2<T> v = pts[k] - pi;
			T vn2 = v.norm2();

			// squared value of dot product of vectors u and v
			T dp = vec2<T>::dot(u, v);
			T dp2 = dp * dp;

			// squared value of L2 distance to point "k"
			dist[k] = vn2 - (dp2 / un2);
		}
	}

	// first and last point have zero distance
	dist[i] = 0;
	dist[j] = 0;
}

template <typename T>
T pts_seg_dist_sum(const vector< vec2<T> >& pts, const size_t i, const size_t j, vector<T>& dist)
{
	// compute distances to all points
	pts_seg_dist(pts, i, j, dist);

	// and sum them
	T distSum = 0;
	for (size_t k = i + 1; k < j; ++k) distSum += dist[k];

	return distSum;
}

template <typename T>
vector<size_t> dp_open(const vector< vec2<T> >& pts, const size_t nPts, const size_t nVert)
{
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
