from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(ext_modules = cythonize(Extension(
    'dp_poly',
    sources=['dp_poly.pyx'],
    language='c++',
    extra_compile_args=['-std=c++11', '-fopenmp'],
    extra_link_args=['-lgomp'],
)))

