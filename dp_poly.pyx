from libcpp.utility cimport pair
from libcpp.vector cimport vector

cdef extern from "dp_poly_python.hpp":
    vector[size_t] dp_poly_open[T](vector[pair[T,T]] pts, size_t nVert)
    vector[size_t] dp_poly_close[T](vector[pair[T,T]] pts, size_t nVert)

def open(pts, num_vert):
    return dp_poly_open[double](pts, num_vert)

def close(pts, num_vert):
    return dp_poly_close[double](pts, num_vert)
