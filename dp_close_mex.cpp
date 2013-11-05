#ifndef NMEX

#include <mex.h>
#include "dp_close.hpp"
#include "mex_utils.hpp"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	run_dp<dp_close>(nlhs, plhs, nrhs, prhs);
}

#endif
