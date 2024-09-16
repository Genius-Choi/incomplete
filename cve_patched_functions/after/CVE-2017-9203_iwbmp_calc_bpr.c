static size_t iwbmp_calc_bpr(int bpp, size_t width)
{
	return ((bpp*width+31)/32)*4;
}
