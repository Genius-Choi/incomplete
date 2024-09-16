static int jp2_getint(jas_stream_t *in, int s, int n, int_fast32_t *val)
{
	int c;
	int i;
	uint_fast32_t v;
	int m;

	m = (n + 7) / 8;

	v = 0;
	for (i = 0; i < m; ++i) {
		if ((c = jas_stream_getc(in)) == EOF) {
			return -1;
		}
		v = (v << 8) | c;
	}
	v &= ONES(n);
	if (s) {
		int sb;
		sb = v & (1 << (8 * m - 1));
		*val = ((~v) + 1) & ONES(8 * m);
		if (sb) {
			*val = -*val;
		}
	} else {
		*val = v;
	}

	return 0;
}
