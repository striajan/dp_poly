% remove old binaries
delete *.mexw64

% compile
mex dp_open_mex.cpp
