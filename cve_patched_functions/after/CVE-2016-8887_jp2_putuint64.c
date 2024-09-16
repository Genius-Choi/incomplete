static int jp2_putuint64(jas_stream_t *out, uint_fast64_t val)
{
	if (jp2_putuint32(out, (val >> 32) & 0xffffffffUL) ||
	  jp2_putuint32(out, val & 0xffffffffUL)) {
		return -1;
	}
	return 0;
}
