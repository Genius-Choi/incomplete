IW_IMPL(void*) iw_malloc_ex(struct iw_context *ctx, unsigned int flags, size_t n)
{
	void *mem;

	if(n>ctx->max_malloc) {
		if(!(flags&IW_MALLOCFLAG_NOERRORS))
			iw_set_error(ctx,"Out of memory");
		return NULL;
	}

	mem = (*ctx->mallocfn)(ctx->userdata,flags,n);

	if(!mem) {
		if(!(flags&IW_MALLOCFLAG_NOERRORS))
			iw_set_error(ctx,"Out of memory");
		return NULL;
	}
	return mem;
}
