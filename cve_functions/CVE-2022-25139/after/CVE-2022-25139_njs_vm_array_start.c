njs_vm_array_start(njs_vm_t *vm, njs_value_t *value)
{
    if (njs_slow_path(!njs_is_fast_array(value))) {
        njs_type_error(vm, "njs_vm_array_start() argument is not a fast array");
        return NULL;
    }

    return njs_array(value)->start;
}
