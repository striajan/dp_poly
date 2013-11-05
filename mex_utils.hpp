#ifndef NMEX

#ifndef MEX_UTILS_HPP_
#define MEX_UTILS_HPP_

#include <mex.h>
#include "dp_base.hpp"

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

template <template<class> class TAlg, typename T>
void run_dp_alg(const mxArray* ptsArg, mxClassID ptsClass, size_t nPts, size_t nVert, size_t* ind)
{
	// convert matrix of coordinates to vector of 2D points
	T* ptsArray = mx_get_data<T>(ptsArg);
	std::vector< vec2<T> > ptsVec(nPts);
	for (size_t i = 0; i < nPts; ++i)
	{
		const T& x = ptsArray[2 * i];
		const T& y = ptsArray[2 * i + 1];
		ptsVec[i] = vec2<T>(x, y);
	}

	// run optimization
	TAlg<T> dp;
	std::vector<size_t> selVec = dp(ptsVec, nVert);

	// convert resulting vector of selected indexes to array
	std::copy(selVec.begin(), selVec.end(), ind);
}

template <template<class> class TAlg>
void run_dp(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if (nrhs != 2)
	{
		mexErrMsgTxt("Two inputs required.");
	}

	if (nlhs != 1)
	{
		mexErrMsgTxt("One output required.");
	}

	const mxArray* ptsArg = prhs[0];
	const mxArray* nVertArg = prhs[1];

	if (mxIsComplex(ptsArg) || mxGetM(ptsArg) != 2)
	{
		mexErrMsgTxt("Points must form a non-complex matrix with two rows.");
	}

	if (mxIsComplex(nVertArg) || mxGetNumberOfElements(nVertArg) != 1)
	{
		mexErrMsgTxt("Number of vertices must be a non-complex scalar.");
	}

	const size_t nPts = mxGetN(ptsArg);
	const size_t nVert = static_cast<size_t>(mxGetScalar(nVertArg));

	size_t* ind = mx_create_numeric_matrix<size_t>(1, nVert, mxUINT64_CLASS, plhs[0]);

	switch (mxGetClassID(ptsArg))
	{
		case mxSINGLE_CLASS:
		{
			run_dp_alg<TAlg, float>(ptsArg, mxSINGLE_CLASS, nPts, nVert, ind);
			break;
		}
		case mxDOUBLE_CLASS:
		{
			run_dp_alg<TAlg, double>(ptsArg, mxSINGLE_CLASS, nPts, nVert, ind);
			break;
		}
		default:
		{
			mexErrMsgTxt("Point coordinates must be single or double.");
			break;
		}
	}
}

#endif // MEX_UTILS_HPP_

#endif // NMEX
