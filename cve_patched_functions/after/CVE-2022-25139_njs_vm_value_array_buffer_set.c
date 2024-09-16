njs_vm_value_array_buffer_set(njs_vm_t *vm, njs_value_t *value,
    const u_char *start, uint32_t size)
{
    njs_array_buffer_t  *array;

    array = njs_array_buffer_alloc(vm, 0, 0);
    if (njs_slow_path(array == NULL)) {
        return NJS_ERROR;
    }

    array->u.data = (u_char *) start;
    array->size = size;

    njs_set_array_buffer(value, array);

    return NJS_OK;
}
