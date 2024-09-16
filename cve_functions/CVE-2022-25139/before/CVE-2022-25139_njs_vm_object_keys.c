njs_vm_object_keys(njs_vm_t *vm, njs_value_t *value, njs_value_t *retval)
{
    njs_array_t  *keys;

    keys = njs_value_own_enumerate(vm, value, NJS_ENUM_KEYS,
                                   NJS_ENUM_STRING, 0);
    if (njs_slow_path(keys == NULL)) {
        return NULL;
    }

    njs_set_array(retval, keys);

    return retval;
}
