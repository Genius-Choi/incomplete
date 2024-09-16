int jp2_validate(jas_stream_t *in)
{
	char buf[JP2_VALIDATELEN];
	int i;
	int n;
#if 0
	jas_stream_t *tmpstream;
	jp2_box_t *box;
#endif

	assert(JAS_STREAM_MAXPUTBACK >= JP2_VALIDATELEN);

	/* Read the validation data (i.e., the data used for detecting
	  the format). */
	if ((n = jas_stream_read(in, buf, JP2_VALIDATELEN)) < 0) {
		return -1;
	}

	/* Put the validation data back onto the stream, so that the
	  stream position will not be changed. */
	for (i = n - 1; i >= 0; --i) {
		if (jas_stream_ungetc(in, buf[i]) == EOF) {
			return -1;
		}
	}

	/* Did we read enough data? */
	if (n < JP2_VALIDATELEN) {
		return -1;
	}

	/* Is the box type correct? */
	if (((buf[4] << 24) | (buf[5] << 16) | (buf[6] << 8) | buf[7]) !=
	  JP2_BOX_JP)
	{
		return -1;
	}

	return 0;
}
