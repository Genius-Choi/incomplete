njs_vm_object_prop(njs_vm_t *vm, njs_value_t *value, const njs_str_t *prop,
    njs_opaque_value_t *retval)
{
    njs_int_t    ret;
    njs_value_t  key;

    if (njs_slow_path(!njs_is_object(value))) {
        njs_type_error(vm, "njs_vm_object_prop() argument is not object");
        return NULL;
    }

    ret = njs_vm_value_string_set(vm, &key, prop->start, prop->length);
    if (njs_slow_path(ret != NJS_OK)) {
        return NULL;
    }

    ret = njs_value_property(vm, value, &key, njs_value_arg(retval));
    if (njs_slow_path(ret != NJS_OK)) {
        return NULL;
    }

    return njs_value_arg(retval);
}
