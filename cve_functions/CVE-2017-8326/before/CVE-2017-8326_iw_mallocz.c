IW_IMPL(void*) iw_mallocz(struct iw_context *ctx, size_t n)
{
	return iw_malloc_ex(ctx,IW_MALLOCFLAG_ZEROMEM,n);
}
