IW_IMPL(size_t) iw_calc_bytesperrow(int num_pixels, int bits_per_pixel)
{
	return (size_t)(((num_pixels*bits_per_pixel)+7)/8);
}
