njs_array_iterator_prototype_next(njs_vm_t *vm, njs_value_t *args,
    njs_uint_t nargs, njs_index_t tag)
{
    njs_int_t          ret;
    njs_bool_t         check;
    njs_value_t        *this;
    njs_object_t       *object;
    njs_object_prop_t  *prop_value, *prop_done;

    this = njs_argument(args, 0);

    check = njs_is_object_value(this)
            && (njs_is_object_data(this, NJS_DATA_TAG_ARRAY_ITERATOR)
                || !njs_is_valid(njs_object_value(this)));

    if (njs_slow_path(!check)) {
        njs_type_error(vm, "Method [Array Iterator].prototype.next"
                           " called on incompatible receiver");
        return NJS_ERROR;
    }

    object = njs_object_alloc(vm);
    if (njs_slow_path(object == NULL)) {
        return NJS_ERROR;
    }

    njs_set_object(&vm->retval, object);

    prop_value = njs_object_property_add(vm, &vm->retval,
                                         njs_value_arg(&string_value), 0);
    if (njs_slow_path(prop_value == NULL)) {
        return NJS_ERROR;
    }

    prop_done = njs_object_property_add(vm, &vm->retval,
                                        njs_value_arg(&string_done), 0);
    if (njs_slow_path(prop_done == NULL)) {
        return NJS_ERROR;
    }

    ret = njs_array_iterator_next(vm, this, &prop_value->value);
    if (njs_slow_path(ret == NJS_ERROR)) {
        return ret;
    }

    if (njs_slow_path(ret == NJS_DECLINED)) {
        njs_set_undefined(&prop_value->value);
        njs_set_boolean(&prop_done->value, 1);

        return NJS_OK;
    }

    njs_set_boolean(&prop_done->value, 0);

    return NJS_OK;
}
