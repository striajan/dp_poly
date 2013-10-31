#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <ostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		os.precision(3);
		os << vec[i] << " ";
	}

	return os;
}


#endif
