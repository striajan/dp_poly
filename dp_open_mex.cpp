#ifndef NMEX

#include <mex.h>
#include "dp_open.hpp"
#include "mex_utils.hpp"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	run_dp<dp_open>(nlhs, plhs, nrhs, prhs);
}

#endif
