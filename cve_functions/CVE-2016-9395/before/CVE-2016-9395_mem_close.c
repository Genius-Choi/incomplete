static int mem_close(jas_stream_obj_t *obj)
{
	JAS_DBGLOG(100, ("mem_close(%p)\n", obj));
	jas_stream_memobj_t *m = (jas_stream_memobj_t *)obj;
	JAS_DBGLOG(100, ("mem_close myalloc=%d\n", m->myalloc_));
	if (m->myalloc_ && m->buf_) {
		JAS_DBGLOG(100, ("mem_close freeing buffer %p\n", m->buf_));
		jas_free(m->buf_);
		m->buf_ = 0;
	}
	jas_free(obj);
	return 0;
}
