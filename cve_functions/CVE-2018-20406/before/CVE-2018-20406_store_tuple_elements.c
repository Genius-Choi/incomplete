store_tuple_elements(PicklerObject *self, PyObject *t, Py_ssize_t len)
{
    Py_ssize_t i;

    assert(PyTuple_Size(t) == len);

    for (i = 0; i < len; i++) {
        PyObject *element = PyTuple_GET_ITEM(t, i);

        if (element == NULL)
            return -1;
        if (save(self, element, 0) < 0)
            return -1;
    }

    return 0;
}
