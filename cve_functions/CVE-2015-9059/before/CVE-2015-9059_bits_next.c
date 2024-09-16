bits_next (int bits)
{
	bits++;
	if (bits > 8) bits = 5;

	return bits;
}
