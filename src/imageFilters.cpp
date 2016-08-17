
// Debug setting for Python 
#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED 1
#undef _DEBUG
#endif

#include <Python.h>
#include "displayImage.h"
#include "MarrHildrethED.h"
#include "OrderStatsFilters.h" 

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG 1
#endif

enum filter { MARRHILDRETH, MEAN, MEDIAN, MIDP, MIN, MAX, MINMAX };

/*
* Function to be called from Python: applyFilter(String path, int filter)
* Filters the given image
*/
static PyObject* applyFilter(PyObject* self, PyObject* args)
{
	// Variable Declaration:
	char *path; filter filterType; int responce = -1; Mat src; 
	// Recive inputs from python	
	PyArg_ParseTuple(args, "si", &path, &filterType);
	//Create Image Matrix
	src = imread(path, 0);
	//If not an image return -1
	if (!src.data)
	{
		return Py_BuildValue("i", responce);
	}
	//Else apply the given filter
		switch (filterType)
		{
		case MARRHILDRETH:
			responce = filterType;
			show(src,marrhildreth(src));
			return Py_BuildValue("i", responce);
			break;
		case MEAN:
			
			responce = filterType;
			show(src, mean(src));
			return Py_BuildValue("i", responce);
			break;
		case MEDIAN:
			responce = filterType;
			show(src, median(src));
			return Py_BuildValue("i", responce);
			break;
		case MIDP:
			responce = filterType;
			show(src, midpoint(src));
			return Py_BuildValue("i", responce);
			break;
		case MIN:
			responce = filterType;
			show(src, min(src));
			return Py_BuildValue("i", responce);
			break;
		case MAX:
			responce = filterType;
			show(src, max(src));
			return Py_BuildValue("i", responce);
			break;
		case MINMAX:
			responce = filterType;
			show(src, min_max(src));
			return Py_BuildValue("i", responce);
			break;
		default:
			return Py_BuildValue("i", responce);
			break;
		}	
}

/*
* Test function to be called from Python
* Returns the string: "Hello World From C/C++"
*/
static PyObject* py_Test(PyObject* self, PyObject* args)
{
	return Py_BuildValue("s", "Hello World From C/C++");
}

/*
* Bind Python function names to our C functions
*/
static PyMethodDef imageFilters_methods[] = {
		{ "applyFilter", (PyCFunction)applyFilter, METH_VARARGS },
		{ "test", py_Test, METH_VARARGS },
		{ NULL, NULL }
};

static struct PyModuleDef moduledef = {
PyModuleDef_HEAD_INIT,
"FilterLibs",
NULL,
-1,
imageFilters_methods
};

PyMODINIT_FUNC PyInit_FilterLibs(void)
{
	PyObject* m;
	m = PyModule_Create(&moduledef);
	if (m == NULL)
		return NULL;

	return m;
}


