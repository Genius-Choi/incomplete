IW_IMPL(double) iw_convert_sample_from_linear(double v, const struct iw_csdescr *csdescr)
{
	return (double)linear_to_x_sample(v,csdescr);
}
