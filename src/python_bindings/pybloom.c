#include <Python.h>

#include "bloom.h"
#include "hash.h"

static PyObject *hash_wrapper(PyObject *self, PyObject *args) {
    const char *string;
    int function_number;

    if (!PyArg_ParseTuple(args, "is", &function_number, &string))
        return NULL;

    uint32_t h = hash(function_number, string);

    return Py_BuildValue("I", h);
}

static bloom_filter_t *filter;

static PyObject *bloom_create_wrapper(PyObject *self, PyObject *args) {
    int capacity;
    double false_positive_rate;


    if (!PyArg_ParseTuple(args, "id", &capacity, &false_positive_rate))
        return NULL;

    filter = bloom_create(capacity, false_positive_rate);

    Py_RETURN_NONE;
//    return Py_None;
}

static PyObject *bloom_put_wrapper(PyObject *self, PyObject *args) {
    const char *string;

    if (!PyArg_ParseTuple(args, "s", &string))
        return NULL;

    bloom_put(filter, string);

    return Py_BuildValue("i", 1);
}

static PyObject *bloom_contains_wrapper(PyObject *self, PyObject *args) {
    const char *string;

    if (!PyArg_ParseTuple(args, "s", &string))
        return NULL;

    int result = bloom_contains(filter, string);

    return Py_BuildValue("i", result);
}

static PyMethodDef module_methods[] = {
    { "hash", (PyCFunction)hash_wrapper, METH_VARARGS, NULL },
    { "create", (PyCFunction)bloom_create_wrapper, METH_VARARGS, NULL },
    { "put", (PyCFunction)bloom_put_wrapper, METH_VARARGS, NULL },
    { "contains", (PyCFunction)bloom_contains_wrapper, METH_VARARGS, NULL },
    { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initpybloom(void) {
    Py_InitModule("pybloom", module_methods);
}
