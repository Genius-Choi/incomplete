njs_async_context_free(njs_vm_t *vm, njs_async_ctx_t *ctx)
{
    njs_mp_free(vm->mem_pool, ctx->capability);
    njs_mp_free(vm->mem_pool, ctx);
}
