IW_IMPL(void*) iw_malloc(struct iw_context *ctx, size_t n)
{
	return iw_malloc_ex(ctx,0,n);
}
