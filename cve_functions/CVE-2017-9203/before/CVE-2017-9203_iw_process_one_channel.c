static int iw_process_one_channel(struct iw_context *ctx, int intermed_channel,
  const struct iw_csdescr *in_csdescr, const struct iw_csdescr *out_csdescr)
{
	if(!iw_process_cols_to_intermediate(ctx,intermed_channel,in_csdescr)) {
		return 0;
	}

	if(!iw_process_rows_intermediate_to_final(ctx,intermed_channel,out_csdescr)) {
		return 0;
	}

	return 1;
}
