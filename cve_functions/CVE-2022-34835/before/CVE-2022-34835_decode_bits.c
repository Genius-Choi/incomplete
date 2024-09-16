static void decode_bits (u_char const b, char const *str[], int const do_once)
{
	u_char mask;

	for (mask = 0x80; mask != 0x00; mask >>= 1, ++str) {
		if (b & mask) {
			puts (*str);
			if (do_once)
				return;
		}
	}
}
