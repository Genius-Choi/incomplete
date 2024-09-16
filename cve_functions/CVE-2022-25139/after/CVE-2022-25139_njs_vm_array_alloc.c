njs_vm_array_alloc(njs_vm_t *vm, njs_value_t *retval, uint32_t spare)
{
    njs_array_t  *array;

    array = njs_array_alloc(vm, 1, 0, spare);

    if (njs_slow_path(array == NULL)) {
        return NJS_ERROR;
    }

    njs_set_array(retval, array);

    return NJS_OK;
}
