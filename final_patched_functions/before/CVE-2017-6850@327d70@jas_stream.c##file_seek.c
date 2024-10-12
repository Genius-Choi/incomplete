static long file_seek(jas_stream_obj_t *obj, long offset, int origin)
{
	jas_stream_fileobj_t *fileobj;
	JAS_DBGLOG(100, ("file_seek(%p, %ld, %d)\n", obj, offset, origin));
	fileobj = JAS_CAST(jas_stream_fileobj_t *, obj);
	return lseek(fileobj->fd, offset, origin);
}
