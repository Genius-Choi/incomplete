UnpicklerMemoProxy_dealloc(UnpicklerMemoProxyObject *self)
{
    PyObject_GC_UnTrack(self);
    Py_XDECREF(self->unpickler);
    PyObject_GC_Del((PyObject *)self);
}
