#ifndef MAT_HPP_
#define MAT_HPP_

#include <algorithm>
#include <cassert>
#include <ostream>
#include <vector>
#include "debug.hpp"

template <typename T>
class mat
	: public std::vector<T>
{
private:

	typedef std::vector<T> vec;

public:

	const size_t m;
	const size_t n;

	mat(size_t m_, size_t n_, const T& val = T())
		: vec(m_ * n_, val), m(m_), n(n_)
	{
	}

	T& operator()(size_t i, size_t j)
	{
		check_range(i, j);
		return (*this)[i + j * m];
	}

	const T& operator()(size_t i, size_t j) const
	{
		check_range(i, j);
		return (*this)[i + j * m];
	}

private:

	void check_range(size_t i, size_t j) const
	{
		assert(0 <= i && i < m);
		assert(0 <= j && j < n);
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const mat<T>& m)
{
	for (size_t i = 0; i < m.m; ++i)
	{
		for (size_t j = 0; j < m.n; ++j)
		{
			os.precision(3);
			os.width(8);
			os << m(i, j);
		}
		os << std::endl;
	}

	return os;
}

#endif
