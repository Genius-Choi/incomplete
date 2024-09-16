njs_iterator_object_handler(njs_vm_t *vm, njs_iterator_handler_t handler,
    njs_iterator_args_t *args, njs_value_t *key, int64_t i)
{
    njs_int_t    ret;
    njs_value_t  prop, *entry;

    if (key != NULL) {
        ret = njs_value_property(vm, args->value, key, &prop);
        if (njs_slow_path(ret == NJS_ERROR)) {
            return ret;
        }

    } else {
        ret = njs_value_property_i64(vm, args->value, i, &prop);
        if (njs_slow_path(ret == NJS_ERROR)) {
            return ret;
        }
    }

    entry = (ret == NJS_OK) ? &prop : njs_value_arg(&njs_value_invalid);

    ret = handler(vm, args, entry, i);
    if (njs_slow_path(ret != NJS_OK)) {
        if (ret == NJS_DONE) {
            return NJS_DONE;
        }

        return NJS_ERROR;
    }

    return ret;
}
