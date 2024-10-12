static int sfile_read(jas_stream_obj_t *obj, char *buf, int cnt)
{
	FILE *fp;
	size_t n;
	int result;
	JAS_DBGLOG(100, ("sfile_read(%p, %p, %d)\n", obj, buf, cnt));
	fp = JAS_CAST(FILE *, obj);
	n = fread(buf, 1, cnt, fp);
	if (n != cnt) {
		result = (!ferror(fp) && feof(fp)) ? 0 : -1;
	}
	result = JAS_CAST(int, n);
	return result;
}
