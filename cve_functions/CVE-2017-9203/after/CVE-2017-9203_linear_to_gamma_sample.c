static IW_INLINE iw_tmpsample linear_to_gamma_sample(iw_tmpsample v_linear, double gamma)
{
	return pow(v_linear,1.0/gamma);
}
