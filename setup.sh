#!/usr/bin/env bash
rm dppoly.so
python dp_poly_setup.py build_ext --inplace
rm dp_poly.cpp
rm -rf build
python dp_poly_test.py

