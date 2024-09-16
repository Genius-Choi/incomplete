char *jas_stream_gets(jas_stream_t *stream, char *buf, int bufsize)
{
	int c;
	char *bufptr;
	assert(bufsize > 0);

	JAS_DBGLOG(100, ("jas_stream_gets(%p, %p, %d)\n", stream, buf, bufsize));

	bufptr = buf;
	while (bufsize > 1) {
		if ((c = jas_stream_getc(stream)) == EOF) {
			break;
		}
		*bufptr++ = c;
		--bufsize;
		if (c == '\n') {
			break;
		}
	}
	*bufptr = '\0';
	return buf;
}
