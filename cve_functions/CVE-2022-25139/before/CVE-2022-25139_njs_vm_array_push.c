njs_vm_array_push(njs_vm_t *vm, njs_value_t *value)
{
    if (njs_slow_path(!njs_is_array(value))) {
        njs_type_error(vm, "njs_vm_array_push() argument is not array");
        return NULL;
    }

    return njs_array_push(vm, njs_array(value));
}
