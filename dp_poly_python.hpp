#ifndef DP_POLY_HPP_
#define DP_POLY_HPP_

#include <utility>
#include <vector>
#include "dp_close.hpp"
#include "dp_open.hpp"

template <template <typename> class TAlg, typename T>
std::vector<size_t> dp_poly(const std::vector< std::pair<T, T> >& pairPts, const size_t nVert)
{
	std::vector< vec2<T> > vecPts;
	vecPts.reserve(pairPts.size());

	for (size_t i = 0; i < pairPts.size(); ++i)
	{
		// convert pair representation to vec2 representation
		const std::pair<T, T>& pp = pairPts[i];
		vec2<T> vp(pp.first, pp.second);
		vecPts.push_back(vp);
	}

	// run the specified DP algorithm
	return TAlg<T>()(vecPts, nVert);
}

template <typename T>
std::vector<size_t> dp_poly_close(const std::vector< std::pair<T, T> >& pts, const size_t nVert)
{
	return dp_poly<dp_close>(pts, nVert);
}

template <typename T>
std::vector<size_t> dp_poly_open(const std::vector< std::pair<T, T> >& pts, const size_t nVert)
{
	return dp_poly<dp_open>(pts, nVert);
}

#endif
