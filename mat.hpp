#ifndef MAT_HPP_
#define MAT_HPP_

#include <vector>

using std::vector;

template <typename T>
class mat
	: public vector<T>
{
private:

	typedef vector<T> vec;

	const size_t m;
	const size_t n;

public:

	mat(size_t m_, size_t n_)
		: vec(m_ * n_), m(m_), n(n_)
	{ }

	reference& at(size_t i, size_t j)
	{
		return vec::at(i * m + j);
	}

	const_reference& at(size_t i, size_t j) const
	{
		return vec::at(i * m + j);
	}
};

#endif
