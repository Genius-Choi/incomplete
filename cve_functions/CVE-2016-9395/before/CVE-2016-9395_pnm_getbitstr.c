static int pnm_getbitstr(jas_stream_t *in, int *val)
{
	int c;
	int_fast32_t v;
	for (;;) {
		if ((c = pnm_getc(in)) == EOF) {
			return -1;
		}
		if (c == '#') {
			for (;;) {
				if ((c = pnm_getc(in)) == EOF) {
					return -1;
				}
				if (c == '\n') {
					break;
				}
			}
		} else if (c == '0' || c == '1') {
			v = c - '0';
			break;
		}
	}
	if (val) {
		*val = v;
	}
	return 0;
}
