#ifndef MEX_UTILS_HPP_
#define MEX_UTILS_HPP_

#include <mex.h>

template <typename T>
T* mx_get_data(const mxArray* array)
{
	// get matrix from the input array
	return static_cast<T*>(mxGetData(array));
}

template <typename T>
T* mx_create_numeric_matrix(size_t m, size_t n, mxClassID class_id, mxArray*& array)
{
	// create numeric matrix and assign it to the output array
	array = mxCreateNumericMatrix(static_cast<mwSize>(m), static_cast<mwSize>(n), class_id, mxREAL);
	return mx_get_data<T>(array);
}

#endif
