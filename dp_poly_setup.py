from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(
    name='DPPoly',
    description='Polygonal approximation of opened and closed curves using dynamic programming',
    version='1.0',
    ext_modules=cythonize(Extension(
        name='dppoly',
        sources=['dp_poly_python.cpp'],
        language='c++',
        extra_compile_args=['-std=c++11', '-fopenmp'],
        extra_link_args=['-lgomp'],
)))
