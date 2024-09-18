njs_vm_meta(njs_vm_t *vm, njs_uint_t index)
{
    njs_vm_meta_t  *metas;

    metas = vm->options.metas;
    if (njs_slow_path(metas == NULL || metas->size <= index)) {
        return -1;
    }

    return metas->values[index];
}
