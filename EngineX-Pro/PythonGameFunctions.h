#pragma once
class PythonGameFunctions {
public:
	typedef PyObject* PythonModuleFunction(PyObject* poSelf, PyObject* PoArgs);
	static int PythonGameFunctions::PlayerGetStatus(DWORD dwType)
	{
		PyObject* args = PyTuple_New(1);
		PyTuple_SetItem(args, 0, PyInt_FromLong(dwType));
		PythonModuleFunction* func = (PythonModuleFunction*)((DWORD)Globals::hEntryBaseAddress + 0x8FE60);
		PyObject* ret = func(NULL, args);
		int value = PyInt_AsLong(ret);
		Py_DECREF(ret);
		Py_DECREF(args);
		Py_DECREF(func);
		return value;
	}
};
