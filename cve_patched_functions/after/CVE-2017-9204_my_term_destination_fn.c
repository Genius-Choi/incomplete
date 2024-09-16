static void my_term_destination_fn(j_compress_ptr cinfo)
{
	struct iwjpegwcontext *wctx = (struct iwjpegwcontext*)cinfo->dest;
	size_t bytesleft;

	bytesleft = wctx->buffer_len - wctx->pub.free_in_buffer;
	if(bytesleft>0) {
		(*wctx->iodescr->write_fn)(wctx->ctx,wctx->iodescr,
			wctx->buffer,bytesleft);
	}
}
