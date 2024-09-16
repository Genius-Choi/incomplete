IW_IMPL(void*) iw_realloc_ex(struct iw_context *ctx, unsigned int flags,
	void *oldmem, size_t oldmem_size, size_t newmem_size)
{
	void *mem;

	if(!oldmem) {
		return iw_malloc_ex(ctx,flags,newmem_size);
	}

	if(newmem_size>ctx->max_malloc) {
		if(!(flags&IW_MALLOCFLAG_NOERRORS))
			iw_set_error(ctx,"Out of memory");
		return NULL;
	}

	mem = emulated_realloc(ctx,flags,oldmem,oldmem_size,newmem_size);

	if(!mem) {
		if(!(flags&IW_MALLOCFLAG_NOERRORS))
			iw_set_error(ctx,"Out of memory");
		return NULL;
	}
	return mem;
}
