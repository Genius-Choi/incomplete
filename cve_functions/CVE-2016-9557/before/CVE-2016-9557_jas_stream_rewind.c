int jas_stream_rewind(jas_stream_t *stream)
{
	JAS_DBGLOG(100, ("jas_stream_rewind(%p)\n", stream));
	return jas_stream_seek(stream, 0, SEEK_SET);
}
