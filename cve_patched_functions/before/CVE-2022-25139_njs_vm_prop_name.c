njs_vm_prop_name(njs_vm_t *vm, njs_object_prop_t *prop, njs_str_t *dst)
{
    if (njs_slow_path(!njs_is_string(&prop->name))) {
        njs_type_error(vm, "property name is not a string");
        return NJS_ERROR;
    }

    njs_string_get(&prop->name, dst);

    return NJS_OK;
}
