njs_await_rejected(njs_vm_t *vm, njs_value_t *args, njs_uint_t nargs,
    njs_index_t unused)
{
    njs_value_t      *value;
    njs_async_ctx_t  *ctx;

    ctx = vm->top_frame->function->context;

    value = njs_arg(args, nargs, 1);

    if (ctx->await->native.pc == ctx->pc) {
        (void) njs_function_call(vm, njs_function(&ctx->capability->reject),
                                 &njs_value_undefined, value, 1, &vm->retval);

        njs_async_context_free(vm, ctx);

        return NJS_ERROR;
    }

    ctx->pc = ctx->await->native.pc;

    return njs_await_fulfilled(vm, args, nargs, unused);
}
