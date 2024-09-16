IW_IMPL(void*) iw_realloc(struct iw_context *ctx, void *oldmem,
	size_t oldmem_size, size_t newmem_size)
{
	return iw_realloc_ex(ctx,0,oldmem,oldmem_size,newmem_size);
}
