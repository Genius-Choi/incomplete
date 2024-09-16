static unsigned int iw_scale_to_int(double s, unsigned int maxcolor)
{
	if(s<=0.0) return 0;
	if(s>=1.0) return maxcolor;
	return (unsigned int)(0.5+s*maxcolor);
}
