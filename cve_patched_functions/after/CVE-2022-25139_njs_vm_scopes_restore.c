njs_vm_scopes_restore(njs_vm_t *vm, njs_native_frame_t *native,
    njs_native_frame_t *previous)
{
    njs_frame_t  *frame;

    vm->top_frame = previous;

    if (native->function->native) {
        return;
    }

    frame = (njs_frame_t *) native;
    frame = frame->previous_active_frame;
    vm->active_frame = frame;
}
