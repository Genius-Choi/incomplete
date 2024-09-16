IW_IMPL(double) iw_convert_sample_to_linear(double v, const struct iw_csdescr *csdescr)
{
	return (double)x_to_linear_sample(v,csdescr);
}
