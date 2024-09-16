static void put_sample_convert_from_linear_flt(struct iw_context *ctx, iw_tmpsample samp_lin,
	   int x, int y, int channel, const struct iw_csdescr *csdescr)
{
	put_raw_sample_flt32(ctx,(double)samp_lin,x,y,channel);
}
