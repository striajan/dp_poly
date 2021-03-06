#ifndef DP_BASE_HPP_
#define DP_BASE_HPP_

#include <algorithm>
#include <limits>
#include <vector>
#include "debug.hpp"
#include "distance.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "vec2.hpp"

template <typename T>
class dp_base
{
public:

	virtual std::vector<size_t> operator()(const std::vector< vec2<T> >& pts, const size_t nVert) const = 0;

	virtual ~dp_base()
	{ }

protected:

	static void fill_dist_row(const size_t nPts, const size_t nVert, const mat<T>& dist,
			mat<T>& cost, mat<size_t>& prev)
	{
		for (size_t j = 1; j <= nPts - nVert + 1; ++j)
		{
			cost(1, j) = dist(0, j);
			prev(1, j) = 0;
		}
	}

	static void fill_cell(const size_t nPts, const mat<T>& dist,
			const size_t i, const size_t j, const size_t k1, const size_t k2,
			mat<T>& cost, mat<size_t>& prev)
	{
		T cmin = std::numeric_limits<T>::max();
		size_t kmin = 0;

		for (size_t k = k1; k <= k2; ++k)
		{
			const T c = cost(i - 1, k) + dist(k % nPts, j % nPts);
			if (c < cmin)
			{
				cmin = c;
				kmin = k;
			}
		}

		cost(i, j) = cmin;
		prev(i, j) = kmin;
	}

};

#endif
