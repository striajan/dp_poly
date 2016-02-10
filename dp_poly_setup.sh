#!/usr/bin/env bash
rm dppoly.so
python dp_poly_setup.py build_ext --inplace
python dp_poly_test.py
