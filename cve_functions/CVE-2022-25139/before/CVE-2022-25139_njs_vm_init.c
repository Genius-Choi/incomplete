njs_vm_init(njs_vm_t *vm)
{
    njs_int_t    ret;
    njs_frame_t  *frame;

    frame = (njs_frame_t *) njs_function_frame_alloc(vm, NJS_FRAME_SIZE);
    if (njs_slow_path(frame == NULL)) {
        njs_memory_error(vm);
        return NJS_ERROR;
    }

    frame->exception.catch = NULL;
    frame->exception.next = NULL;
    frame->previous_active_frame = NULL;

    vm->active_frame = frame;

    ret = njs_regexp_init(vm);
    if (njs_slow_path(ret != NJS_OK)) {
        return NJS_ERROR;
    }

    ret = njs_builtin_objects_clone(vm, &vm->global_value);
    if (njs_slow_path(ret != NJS_OK)) {
        return NJS_ERROR;
    }

    njs_lvlhsh_init(&vm->values_hash);
    njs_lvlhsh_init(&vm->keywords_hash);
    njs_lvlhsh_init(&vm->modules_hash);
    njs_lvlhsh_init(&vm->events_hash);

    njs_queue_init(&vm->posted_events);
    njs_queue_init(&vm->promise_events);

    return NJS_OK;
}
