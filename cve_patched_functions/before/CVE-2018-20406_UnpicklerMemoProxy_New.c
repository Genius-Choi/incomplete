UnpicklerMemoProxy_New(UnpicklerObject *unpickler)
{
    UnpicklerMemoProxyObject *self;

    self = PyObject_GC_New(UnpicklerMemoProxyObject,
                           &UnpicklerMemoProxyType);
    if (self == NULL)
        return NULL;
    Py_INCREF(unpickler);
    self->unpickler = unpickler;
    PyObject_GC_Track(self);
    return (PyObject *)self;
}
