load_list(UnpicklerObject *self)
{
    PyObject *list;
    Py_ssize_t i;

    if ((i = marker(self)) < 0)
        return -1;

    list = Pdata_poplist(self->stack, i);
    if (list == NULL)
        return -1;
    PDATA_PUSH(self->stack, list, -1);
    return 0;
}
