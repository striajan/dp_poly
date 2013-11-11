#ifndef DP_CLOSE_HPP_
#define DP_CLOSE_HPP_

#include <algorithm>
#include <limits>
#include <vector>
#include "debug.hpp"
#include "distance.hpp"
#include "dp_base.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

template <typename T>
struct dp_close : public dp_base<T>
{
private:

	typedef dp_base<T> base;

public:

	std::vector<size_t> operator()(const std::vector< vec2<T> >& pts, const size_t nVert) const
	{
		const size_t nPts = pts.size();

		// precompute points to segments distances
		const mat<T> dist = pts_seg_dist_sum_cyc(pts);

		// initialize costs and previous pointers for single approximating segment
		mat<T> cost(2 * nVert + 1, 2 * nPts + 1, -1);
		mat<size_t> prev(2 * nVert + 1, 2 * nPts + 1, 9999);
		cost(0, 0) = 0;
		prev(0, 0) = 0;
		base::fill_dist_row(nPts, nVert, dist, cost, prev);

		// first cycle (i = 2..nVert)
		for (size_t i = 2; i <= nVert; ++i)
		{
			for (size_t j = i; j <= nPts - nVert + i; ++j)
			{
				const size_t k1 = i - 1;
				const size_t k2 = j - 1;
				base::fill_cell(nPts, dist, i, j, k1, k2, cost, prev);
			}
		}

		// long row (i = nVert)
		for (size_t j = nPts + 1; j < 2 * nPts - nVert + 1; ++j)
		{
			const size_t k1 = std::max(nVert - 1, j - nPts + 1);
			const size_t k2 = nPts - 1;
			base::fill_cell(nPts, dist, nVert, j, k1, k2, cost, prev);
		}

		// row above long row (i = nVert+1)
		for (size_t j = nPts + 1; j < 2 * nPts - nVert + 2; ++j)
		{
			const size_t k1 = std::max(nVert, j - nPts + 1);
			const size_t k2 = j - 1;
			base::fill_cell(nPts, dist, nVert + 1, j, k1, k2, cost, prev);
		}

		// second cycle (i = nVert+2..2*nVert)
		for (size_t i = nVert + 2; i <= 2 * nVert; ++i)
		{
			for (size_t j = i - nVert + nPts; j <= 2 * nPts - 2 * nVert + i; ++j)
			{
				const size_t k1 = i - nVert + nPts - 1;
				const size_t k2 = j - 1;
				base::fill_cell(nPts, dist, i, j, k1, k2, cost, prev);
			}
		}

		// full path, optimal sub-path and its estimated cost
		std::vector<size_t> path(2 * nVert + 1);
		std::vector<size_t> ind(nVert, 0);
		T minCost = std::numeric_limits<T>::max();

		// select conjugated points having the minimal estimated cost
		for (size_t i = nVert; i <= 2 * nVert; ++i)
		{
			for (size_t j = i - nVert + nPts; j <= 2 * nPts - 2 * nVert + i; ++j)
			{
				// begin with the point in the second half of the state space
				path[i] = j;

				// backtrack; k is unsigned so (k = -1) => (k = max(size_t)) => (k >= i)
				for (size_t k = i - 1; k < i; --k)
				{
					// always continue to the previous point on the optimal path from beginning
					path[k] = prev(k + 1, path[k + 1]);

					// first point has to be in the first half and second point has to be in path;
					// the points have to be conjugated (one cycle far away from each other)
					if ((k <= nVert) && (k + nVert <= i) && (path[k] + nPts == path[k + nVert]))
					{
						const T c1 = cost(k, path[k]);
						const T c2 = cost(k + nVert, path[k + nVert]);
						const T c = c2 - c1;
						if (c < minCost)
						{
							minCost = c;
							std::copy(path.begin() + k, path.begin() + k + nVert, ind.begin());
						}
					}
				}
			}
		}

		// ensure that all indices are in range {0,...,nPts-1}
		for (size_t i = 0; i < nVert; ++i) ind[i] = ind[i] % nPts;

		// rotate indices so that the least one goes first
		std::vector<size_t>::iterator it = std::min_element(ind.begin(), ind.end());
		std::rotate(ind.begin(), it, ind.end());

		return ind;
	}

};

#endif
