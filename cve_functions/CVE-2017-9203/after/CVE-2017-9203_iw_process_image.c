IW_IMPL(int) iw_process_image(struct iw_context *ctx)
{
	int ret;
	int retval = 0;

	if(ctx->use_count>0) {
		iw_set_error(ctx,"Internal: Incorrect attempt to reprocess image");
		goto done;
	}
	ctx->use_count++;

	ret = iw_prepare_processing(ctx,ctx->canvas_width,ctx->canvas_height);
	if(!ret) goto done;

	ret = iw_process_internal(ctx);
	if(!ret) goto done;

	iwpvt_optimize_image(ctx);

	retval = 1;
done:
	return retval;
}
