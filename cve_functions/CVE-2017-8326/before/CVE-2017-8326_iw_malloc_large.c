IW_IMPL(void*) iw_malloc_large(struct iw_context *ctx, size_t n1, size_t n2)
{
	if(n1 > ctx->max_malloc/n2) {
		iw_set_error(ctx,"Image too large to process");
		return NULL;
	}
	return iw_malloc_ex(ctx,0,n1*n2);
}
