#include <Python.h>

#include "hash.h"

static PyObject *hash_wrapper(PyObject *self, PyObject *args) {
    const char *string;
    int function_number;

    uint32_t h;

    if (!PyArg_ParseTuple(args, "is", &function_number, &string))
        return NULL;

    h = hash(function_number, string);

    return Py_BuildValue("I", h);
}

static PyMethodDef module_methods[] = {
    { "hash", (PyCFunction)hash_wrapper, METH_VARARGS, NULL },
    { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initpybloom(void) {
    Py_InitModule("pybloom", module_methods);
}
