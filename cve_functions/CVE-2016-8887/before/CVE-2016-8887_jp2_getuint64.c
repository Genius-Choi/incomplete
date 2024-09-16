static int jp2_getuint64(jas_stream_t *in, uint_fast64_t *val)
{
	uint_fast64_t tmpval;
	int i;
	int c;

	tmpval = 0;
	for (i = 0; i < 8; ++i) {
		tmpval <<= 8;
		if ((c = jas_stream_getc(in)) == EOF) {
			return -1;
		}
		tmpval |= (c & 0xff);
	}
	*val = tmpval;

	return 0;
}
