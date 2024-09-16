static int sfile_close(jas_stream_obj_t *obj)
{
	FILE *fp;
	JAS_DBGLOG(100, ("sfile_close(%p)\n", obj));
	fp = JAS_CAST(FILE *, obj);
	return fclose(fp);
}
