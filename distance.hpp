#ifndef DISTANCE_HPP_
#define DISTANCE_HPP_

#include <vector>
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

#endif
