njs_vm_function(njs_vm_t *vm, const njs_str_t *path)
{
    njs_int_t    ret;
    njs_value_t  retval;

    ret = njs_vm_value(vm, path, &retval);
    if (njs_slow_path(ret != NJS_OK || !njs_is_function(&retval))) {
        return NULL;
    }

    return njs_function(&retval);
}
