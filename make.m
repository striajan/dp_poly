fprintf('Removing old binaries...\n');
delete *.mexw64

fprintf('Compiling DP algorithm for open curves...\n');
mex dp_open_mex.cpp COMPFLAGS="/openmp $COMPFLAGS"

fprintf('Compiling DP algorithm for close curves...\n');
mex dp_close_mex.cpp COMPFLAGS="/openmp $COMPFLAGS"
