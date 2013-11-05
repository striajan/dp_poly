#ifndef DP_OPEN_HPP_
#define DP_OPEN_HPP_

#include <vector>
#include "debug.hpp"
#include "distance.hpp"
#include "dp_base.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

template <typename T>
class dp_open : public dp_base<T>
{
private:

	typedef dp_base<T> base;

public:

	std::vector<size_t> operator()(const std::vector< vec2<T> >& pts, const size_t nVert) const
	{
		const size_t nPts = pts.size();

		// precompute points to segments distances
		const mat<T> dist = pts_seg_dist_sum_seq(pts);

		// initialize costs and previous pointers for single approximating segment
		mat<T> cost(nVert, nPts);
		mat<size_t> prev(nVert, nPts);
		base::fill_dist_row(nPts, nVert, dist, cost, prev);

		// compute all cost and previous pointers
		for (size_t i = 2; i < nVert; ++i)
		{
			for (size_t j = i; j <= nPts - nVert + i; ++j)
			{
				const size_t k1 = i - 1;
				const size_t k2 = j - 1;
				base::fill_cell(nPts, dist, i, j, k1, k2, cost, prev);
			}
		}

		// trace the optimal path
		const std::vector<size_t> ind = base::trace_path(nPts, nVert, nVert - 1, nPts - 1, prev);
		DPRINTLN("INDICES:\n" << ind);

		return ind;
	}
};

#endif
