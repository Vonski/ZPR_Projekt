//#ifdef _DEBUG
//#undef _DEBUG
//#include <Python.h>
//#define _DEBUG
//#else
//#include <Python.h>
//#endif
#include "TwitterNotifier.hpp"
#include <Python.h>
#include <string>


using namespace std;

void TwitterNotifier::tweet(const char* msg) {
	Py_Initialize();
	PyObject* pValue = PyUnicode_FromString(msg);
	PyObject* pArgs;
	pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, pValue);
	PyRun_SimpleString("exec(open('Twitter.py').read())");
	PyObject* main_module = PyImport_AddModule("__main__");
	PyObject* global_dict = PyModule_GetDict(main_module);
	PyObject* func = PyDict_GetItemString(global_dict, "tweet");
	PyObject_CallObject(func, pArgs);
	Py_Finalize();
}