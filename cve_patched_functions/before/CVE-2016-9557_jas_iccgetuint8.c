static int jas_iccgetuint8(jas_stream_t *in, jas_iccuint8_t *val)
{
	int c;
	if ((c = jas_stream_getc(in)) == EOF)
		return -1;
	*val = c;
	return 0;
}
