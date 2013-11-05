#ifndef NMEX

#include <mex.h>
#include <vector>
#include "dp_close.hpp"
#include "mex_utils.hpp"
#include "vec2.hpp"

template <typename T>
void run_dp_close(const mxArray* ptsArg, mxClassID ptsClass, size_t nPts, size_t nVert, size_t* ind)
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
	std::vector<size_t> selVec = dp_close(ptsVec, nVert);

	// convert resulting vector of selected indexes to array
	std::copy(selVec.begin(), selVec.end(), ind);
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
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
				run_dp_close<float>(ptsArg, mxSINGLE_CLASS, nPts, nVert, ind);
				break;
			}
			case mxDOUBLE_CLASS:
			{
				run_dp_close<double>(ptsArg, mxSINGLE_CLASS, nPts, nVert, ind);
				break;
			}
			default:
			{
				mexErrMsgTxt("Point coordinates must be single or double.");
				break;
			}
		}
}

#endif
