static IW_INLINE iw_tmpsample gamma_to_linear_sample(iw_tmpsample v, double gamma)
{
	return pow(v,gamma);
}
