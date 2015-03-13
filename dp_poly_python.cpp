#include <python2.7/Python.h>
#include <numpy/arrayobject.h>
#include <iostream>
#include <vector>
#include "dp_close.hpp"
#include "dp_open.hpp"
#include "vec2.hpp"

static double read_coord(PyArrayObject* array, size_t i, size_t c)
{
	void* valPtr = PyArray_GETPTR2(array, i, c);
	PyObject* valObj = PyArray_GETITEM(array, valPtr);
	double val = PyFloat_AsDouble(valObj);
	return val;
}

template <typename dp_poly_t>
static PyObject* dp_poly_generic(PyObject* args)
{
	PyObject* arrayObj = NULL;
	size_t nVert = 0;
	if (!PyArg_ParseTuple(args, "Oi", &arrayObj, &nVert) || NULL == arrayObj)
	{
		PyErr_SetString(PyExc_RuntimeError, "The input parameters cannot be parsed.");
		return NULL;
	}

	PyTypeObject* arrayTypeObj = arrayObj->ob_type;
	if (0 != strcmp("numpy.ndarray", arrayTypeObj->tp_name))
	{
		PyErr_SetString(PyExc_TypeError, "The input parameter in not of type NumPy array.");
		return NULL;
	}

	PyArrayObject* array = (PyArrayObject*)arrayObj;
	if (2 != array->nd)
	{
		PyErr_SetString(PyExc_ValueError, "The input array is expected to have dimension 2.");
		return NULL;
	}

	size_t nPts = array->dimensions[0];
	if (2 != array->dimensions[1] || nPts < 3)
	{
		PyErr_SetString(PyExc_ValueError,
			"The input array is expected to have size Nx2 representing N points of dimension 2 where N is at least 3.");
		return NULL;
	}

	if (nVert < 3 || nPts < nVert)
	{
		PyErr_SetString(PyExc_ValueError,
			"The number of approximating vertices has to be at least 3 and at most equal to number of points.");
		return NULL;
	}

	// read the point coordinates
	std::vector< vec2<double> > pts(nPts);
	for (size_t j = 0; j < nPts; ++j)
	{
		pts[j].x = read_coord(array, j, 0);
		pts[j].y = read_coord(array, j, 1);
	}

	// compute the polyline / polygonal approximation of the points
	dp_poly_t dp;
	vector<size_t> ind = dp(pts, nVert);

	// build the output list of vertex indices
	PyObject* listObj = PyList_New(nVert);
	for (size_t i = 0; i < nVert; ++i)
	{
		PyObject* indObj = Py_BuildValue("i", ind[i]);
		PyList_SetItem(listObj, i, indObj);
	}

	return listObj;
}

static PyObject* dp_poly_open(PyObject* self, PyObject* args)
{
	return dp_poly_generic< dp_open<double> >(args);
}

static PyObject* dp_poly_close(PyObject* self, PyObject* args)
{
	return dp_poly_generic< dp_close<double> >(args);
}

static PyMethodDef dp_poly_methods[] =
{
	{"open", dp_poly_open, METH_VARARGS, "Compute polyline approximation of the opened curve."},
	{"close", dp_poly_close, METH_VARARGS, "Compute polygonal approximation of the closed curve."},
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initdppoly(void)
{
	Py_InitModule("dppoly", dp_poly_methods);
}

int main(int argc, char* argv[])
{
	Py_SetProgramName(argv[0]);
	Py_Initialize();
	initdppoly();
}
