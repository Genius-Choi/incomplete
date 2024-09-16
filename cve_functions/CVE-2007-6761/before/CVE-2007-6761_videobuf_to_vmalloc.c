void *videobuf_to_vmalloc (struct videobuf_buffer *buf)
{
	struct videbuf_vmalloc_memory *mem=buf->priv;
	BUG_ON (!mem);
	MAGIC_CHECK(mem->magic,MAGIC_VMAL_MEM);

	return mem->vmalloc;
}
