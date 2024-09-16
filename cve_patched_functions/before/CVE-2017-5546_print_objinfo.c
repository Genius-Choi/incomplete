static void print_objinfo(struct kmem_cache *cachep, void *objp, int lines)
{
	int i, size;
	char *realobj;

	if (cachep->flags & SLAB_RED_ZONE) {
		pr_err("Redzone: 0x%llx/0x%llx\n",
		       *dbg_redzone1(cachep, objp),
		       *dbg_redzone2(cachep, objp));
	}

	if (cachep->flags & SLAB_STORE_USER) {
		pr_err("Last user: [<%p>](%pSR)\n",
		       *dbg_userword(cachep, objp),
		       *dbg_userword(cachep, objp));
	}
	realobj = (char *)objp + obj_offset(cachep);
	size = cachep->object_size;
	for (i = 0; i < size && lines; i += 16, lines--) {
		int limit;
		limit = 16;
		if (i + limit > size)
			limit = size - i;
		dump_line(realobj, i, limit);
	}
}
