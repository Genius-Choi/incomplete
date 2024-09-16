static unsigned int calc_sample_convert_from_linear(struct iw_context *ctx, iw_tmpsample samp_lin,
	   const struct iw_csdescr *csdescr, double overall_maxcolorcode)
{
	double s_lin_floor_1, s_lin_ceil_1;
	double s_cvt_floor_full, s_cvt_ceil_full;
	double d_floor, d_ceil;
	int is_exact;
	double s_full;

	if(samp_lin<0.0) samp_lin=0.0;
	if(samp_lin>1.0) samp_lin=1.0;

	is_exact = get_nearest_valid_colors(ctx,samp_lin,csdescr,
		&s_lin_floor_1, &s_lin_ceil_1,
		&s_cvt_floor_full, &s_cvt_ceil_full,
		overall_maxcolorcode, 0);

	if(is_exact) {
		s_full = s_cvt_floor_full;
		goto okay;
	}

	d_floor = samp_lin-s_lin_floor_1;
	d_ceil  = s_lin_ceil_1-samp_lin;

	if(d_ceil<=d_floor) s_full=s_cvt_ceil_full;
	else s_full=s_cvt_floor_full;

okay:
	return (unsigned int)(0.5+s_full);
}
