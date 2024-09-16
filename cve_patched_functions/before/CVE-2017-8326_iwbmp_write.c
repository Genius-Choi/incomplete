static void iwbmp_write(struct iwbmpwcontext *wctx, const void *buf, size_t n)
{
	(*wctx->iodescr->write_fn)(wctx->ctx,wctx->iodescr,buf,n);
	wctx->total_written+=n;
}
