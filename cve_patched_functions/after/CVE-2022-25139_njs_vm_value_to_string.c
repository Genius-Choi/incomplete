njs_vm_value_to_string(njs_vm_t *vm, njs_str_t *dst, njs_value_t *src)
{
    u_char       *start;
    size_t       size;
    njs_int_t    ret;
    njs_value_t  value, stack;

    if (njs_slow_path(src == NULL)) {
        return NJS_ERROR;
    }

    if (njs_is_error(src)) {
        if (njs_is_memory_error(vm, src)) {
            njs_string_get(&njs_string_memory_error, dst);
            return NJS_OK;
        }

        ret = njs_error_stack(vm, src, &stack);
        if (njs_slow_path(ret == NJS_ERROR)) {
            return ret;
        }

        if (ret == NJS_OK) {
            src = &stack;
        }
    }

    value = *src;

    ret = njs_value_to_string(vm, &value, &value);

    if (njs_fast_path(ret == NJS_OK)) {
        size = value.short_string.size;

        if (size != NJS_STRING_LONG) {
            start = njs_mp_alloc(vm->mem_pool, size);
            if (njs_slow_path(start == NULL)) {
                njs_memory_error(vm);
                return NJS_ERROR;
            }

            memcpy(start, value.short_string.start, size);

        } else {
            size = value.long_string.size;
            start = value.long_string.data->start;
        }

        dst->length = size;
        dst->start = start;
    }

    return ret;
}
