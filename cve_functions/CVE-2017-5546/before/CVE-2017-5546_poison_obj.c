static void poison_obj(struct kmem_cache *cachep, void *addr, unsigned char val)
{
	int size = cachep->object_size;
	addr = &((char *)addr)[obj_offset(cachep)];

	memset(addr, val, size);
	*(unsigned char *)(addr + size - 1) = POISON_END;
}
