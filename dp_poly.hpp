#ifndef DP_POLY_HPP_
#define DP_POLY_HPP_

#include <iostream>
#include "vec2.hpp"

template <typename T>
void pts_seg_dist(const vec2<T>* pts, const size_t i, const size_t j, T* dist)
{
	typedef vec2<T> vec2t;

	if (j - i >= 0)
	{
		// first point "i" of the segment
		const vec2t& pi = pts[i];

		// vector u connecting first point "i" with last "j"
		vec2t u = pts[j] - pts[i];
		T un2 = u.norm2();

		// compute distances to all inner points
		for (size_t k = i + 1; k < j; ++k)
		{
			// vector v connecting first point "i" with point "k"
			vec2t v = pts[k] - pi;
			T vn2 = v.norm2();

			// squared value of dot product of vectors u and v
			T dp = vec2t::dot(u, v);
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
T pts_seg_dist_sum(const vec2<T>* pts, const size_t i, const size_t j, T* dist)
{
	// compute distances to all points
	pts_seg_dist(pts, i, j, dist);

	// and sum them
	T distSum = 0;
	for (size_t k = i + 1; k < j; ++k) distSum += dist[k];

	return distSum;
}

template <typename T>
void dp_open(const vec2<T>* pts, const size_t nPts)
{
	T* dist = new T[nPts * nPts];
	T* distBuff = new T[nPts];

	for (size_t i = 0; i < nPts; ++i)
	{
		for (size_t j = i; j < nPts; ++j)
		{
			dist[i * nPts + j] = pts_seg_dist_sum(pts, i, j, distBuff);
			std::cout << dist[i * nPts + j] <<  " ";
		}
		std::cout << std::endl;
	}

	delete [] distBuff;
	delete [] dist;
}

#endif
