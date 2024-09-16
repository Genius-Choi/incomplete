load_binint2(UnpicklerObject *self)
{
    char *s;

    if (_Unpickler_Read(self, &s, 2) < 0)
        return -1;

    return load_binintx(self, s, 2);
}
