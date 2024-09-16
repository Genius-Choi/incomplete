static IW_INLINE iw_tmpsample linear_to_srgb_sample(iw_tmpsample v_linear)
{
	if(v_linear <= 0.0031308) {
		return 12.92*v_linear;
	}
	return 1.055*pow(v_linear,1.0/2.4) - 0.055;
}
