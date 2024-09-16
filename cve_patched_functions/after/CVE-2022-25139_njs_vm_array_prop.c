njs_vm_array_prop(njs_vm_t *vm, njs_value_t *value, int64_t index,
    njs_opaque_value_t *retval)
{
    njs_int_t    ret;
    njs_array_t  *array;

    if (njs_slow_path(!njs_is_object(value))) {
        njs_type_error(vm, "njs_vm_array_prop() argument is not object");
        return NULL;
    }

    if (njs_fast_path(njs_is_fast_array(value))) {
        array = njs_array(value);

        if (index >= 0 && index < array->length) {
            return &array->start[index];
        }

        return NULL;
    }

    ret = njs_value_property_i64(vm, value, index, njs_value_arg(retval));
    if (njs_slow_path(ret != NJS_OK)) {
        return NULL;
    }

    return njs_value_arg(retval);
}
