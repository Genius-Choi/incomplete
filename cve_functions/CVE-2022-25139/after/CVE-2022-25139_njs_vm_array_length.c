njs_vm_array_length(njs_vm_t *vm, njs_value_t *value, int64_t *length)
{
    if (njs_fast_path(njs_is_array(value))) {
        *length = njs_array(value)->length;
    }

    return njs_object_length(vm, value, length);
}
