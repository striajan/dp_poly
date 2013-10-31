#ifndef DISTANCE_HPP_
#define DISTANCE_HPP_

#include <algorithm>
#include <vector>
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
mat<T> pts_seg_dist_sum_seq(const vector< vec2<T> >& pts)
{
	size_t nPts = pts.size();

	mat<T> dist(nPts, nPts, 0);
	vector<T> distBuff(nPts);

	for (size_t j = 0; j < nPts - 2; ++j)
	{
		for (size_t k = j + 2; k < nPts; ++k)
		{
			dist(j, k) = pts_seg_dist_sum(pts, j, k, distBuff);
		}
	}

	return dist;
}

template <typename T>
mat<T> pts_seg_dist_sum_cyc(const vector< vec2<T> >& pts)
{
	size_t nPts = pts.size();

	// create vector containing all points in two sequences
	vector< vec2<T> > pts2(2 * nPts);
	std::copy(pts.begin(), pts.end(), pts2.begin());
	std::copy(pts.begin(), pts.end(), pts2.begin() + nPts);

	mat<T> dist(nPts, nPts, 0);
	vector<T> distBuff2(2 * nPts);

	for (size_t j = 0; j < nPts; ++j)
	{
		for (size_t k = j + 2; k < j + nPts; ++k)
		{
			dist(j, k % nPts) = pts_seg_dist_sum(pts2, j, k, distBuff2);
		}
	}

	return dist;
}

#endif
