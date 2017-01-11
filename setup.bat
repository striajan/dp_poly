del dppoly.pyd
python dp_poly_setup.py build_ext --inplace
del dp_poly.cpp
rmdir /s /q build
python dp_poly_test.py

