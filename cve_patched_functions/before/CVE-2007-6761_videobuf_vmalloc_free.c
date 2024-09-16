void videobuf_vmalloc_free (struct videobuf_buffer *buf)
{
	struct videbuf_vmalloc_memory *mem=buf->priv;
	BUG_ON (!mem);

	MAGIC_CHECK(mem->magic,MAGIC_VMAL_MEM);

	vfree(mem->vmalloc);
	mem->vmalloc=NULL;

	return;
}
