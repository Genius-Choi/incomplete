Pickler_clear(PicklerObject *self)
{
    Py_CLEAR(self->output_buffer);
    Py_CLEAR(self->write);
    Py_CLEAR(self->pers_func);
    Py_CLEAR(self->dispatch_table);
    Py_CLEAR(self->fast_memo);

    if (self->memo != NULL) {
        PyMemoTable *memo = self->memo;
        self->memo = NULL;
        PyMemoTable_Del(memo);
    }
    return 0;
}
