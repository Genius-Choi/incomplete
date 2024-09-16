IW_IMPL(int) iw_round_to_int(double x)
{
	if(x<0.0) return -(int)(0.5-x);
	return (int)(0.5+x);
}
