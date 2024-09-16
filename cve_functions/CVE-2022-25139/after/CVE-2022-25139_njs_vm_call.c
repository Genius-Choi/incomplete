njs_vm_call(njs_vm_t *vm, njs_function_t *function, const njs_value_t *args,
    njs_uint_t nargs)
{
    return njs_vm_invoke(vm, function, args, nargs, &vm->retval);
}
