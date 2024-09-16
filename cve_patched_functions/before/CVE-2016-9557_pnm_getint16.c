static int pnm_getint16(jas_stream_t *in, int *val)
{
	int v;
	int c;

	if ((c = jas_stream_getc(in)) == EOF) {
		return -1;
	}
	v = c & 0xff;
	if ((c = jas_stream_getc(in)) == EOF) {
		return -1;
	}
	v = (v << 8) | (c & 0xff);
	*val = v;

	return 0;
}
