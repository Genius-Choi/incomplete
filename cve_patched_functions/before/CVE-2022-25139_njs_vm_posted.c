njs_vm_posted(njs_vm_t *vm)
{
    return njs_posted_events(vm) || njs_promise_events(vm);
}
