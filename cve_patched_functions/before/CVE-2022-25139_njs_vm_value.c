njs_vm_value(njs_vm_t *vm, const njs_str_t *path, njs_value_t *retval)
{
    u_char       *start, *p, *end;
    size_t       size;
    njs_int_t    ret;
    njs_value_t  value, key;

    start = path->start;
    end = start + path->length;

    njs_set_object(&value, &vm->global_object);

    for ( ;; ) {
        p = njs_strlchr(start, end, '.');

        size = ((p != NULL) ? p : end) - start;
        if (njs_slow_path(size == 0)) {
            njs_type_error(vm, "empty path element");
            return NJS_ERROR;
        }

        ret = njs_string_set(vm, &key, start, size);
        if (njs_slow_path(ret != NJS_OK)) {
            return NJS_ERROR;
        }

        ret = njs_value_property(vm, &value, &key, njs_value_arg(retval));
        if (njs_slow_path(ret != NJS_OK)) {
            return ret;
        }

        if (p == NULL) {
            break;
        }

        start = p + 1;
        value = *retval;
    }

    return NJS_OK;
}
