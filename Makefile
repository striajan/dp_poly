dp_close:
	mex dp_close_mex.cpp

dp_open:
	mex dp_open_mex.cpp

all: dp_close dp_open

clean:
	rm *.mexa64

