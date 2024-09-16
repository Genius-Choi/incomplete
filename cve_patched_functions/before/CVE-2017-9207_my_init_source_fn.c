static void my_init_source_fn(j_decompress_ptr cinfo)
{
	struct iwjpegrcontext *rctx = (struct iwjpegrcontext*)cinfo->src;
	rctx->pub.next_input_byte = rctx->buffer;
	rctx->pub.bytes_in_buffer = 0;
}
