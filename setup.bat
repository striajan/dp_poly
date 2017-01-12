del /q dppoly.pyd

python setup.py build_ext --inplace

del /q dp_poly.cpp
rmdir /s /q build

python dp_poly_test.py

