njs_vm_value_to_bytes(njs_vm_t *vm, njs_str_t *dst, njs_value_t *src)
{
    u_char              *start;
    size_t              size, length, offset;
    njs_int_t           ret;
    njs_value_t         value;
    njs_typed_array_t   *array;
    njs_array_buffer_t  *buffer;

    if (njs_slow_path(src == NULL)) {
        return NJS_ERROR;
    }

    ret = NJS_OK;
    value = *src;

    switch (value.type) {
    case NJS_TYPED_ARRAY:
    case NJS_DATA_VIEW:
    case NJS_ARRAY_BUFFER:

        if (value.type != NJS_ARRAY_BUFFER) {
            array = njs_typed_array(&value);
            buffer = njs_typed_array_buffer(array);
            offset = array->offset;
            length = array->byte_length;

        } else {
            buffer = njs_array_buffer(&value);
            offset = 0;
            length = buffer->size;
        }

        if (njs_slow_path(njs_is_detached_buffer(buffer))) {
            njs_type_error(vm, "detached buffer");
            return NJS_ERROR;
        }

        dst->start = &buffer->u.u8[offset];
        dst->length = length;
        break;

    default:
        ret = njs_value_to_string(vm, &value, &value);
        if (njs_slow_path(ret != NJS_OK)) {
            return NJS_ERROR;
        }

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
