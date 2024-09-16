njs_vm_value_buffer_set(njs_vm_t *vm, njs_value_t *value, const u_char *start,
    uint32_t size)
{
    return njs_buffer_set(vm, value, start, size);
}
