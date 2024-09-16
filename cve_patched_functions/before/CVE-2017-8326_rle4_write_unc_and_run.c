static void rle4_write_unc_and_run(struct rle_context *rlectx)
{
	iw_byte dstbuf[2];

	rle4_write_unc(rlectx);

	if(rlectx->run_len<1) {
		return;
	}
	if(rlectx->run_len>255) {
		iw_set_error(rlectx->ctx,"Internal: RLE encode error 6");
		return;
	}

	dstbuf[0] = (iw_byte)rlectx->run_len;
	dstbuf[1] = rlectx->run_byte;
	iwbmp_write(rlectx->wctx,dstbuf,2);
	rlectx->total_bytes_written+=2;

	rlectx->pending_data_start+=rlectx->run_len;
	rlectx->run_len=0;
}
