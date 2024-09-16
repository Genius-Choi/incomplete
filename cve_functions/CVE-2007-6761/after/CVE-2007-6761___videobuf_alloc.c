static void *__videobuf_alloc(size_t size)
{
	struct videbuf_vmalloc_memory *mem;
	struct videobuf_buffer *vb;

	vb = kzalloc(size+sizeof(*mem),GFP_KERNEL);

	mem = vb->priv = ((char *)vb)+size;
	mem->magic=MAGIC_VMAL_MEM;

	dprintk(1,"%s: allocated at %p(%ld+%ld) & %p(%ld)\n",
		__FUNCTION__,vb,(long)sizeof(*vb),(long)size-sizeof(*vb),
		mem,(long)sizeof(*mem));

	return vb;
}
