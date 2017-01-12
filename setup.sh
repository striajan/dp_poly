#!/usr/bin/env bash

rm -f dppoly.so

python setup.py build_ext --inplace

rm -f dp_poly.cpp
rm -rf build

#python dp_poly_test.py

