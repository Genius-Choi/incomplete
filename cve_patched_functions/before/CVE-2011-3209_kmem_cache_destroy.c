void kmem_cache_destroy(struct kmem_cache *s)
{
	down_write(&slub_lock);
	s->refcount--;
	if (!s->refcount) {
		list_del(&s->list);
		up_write(&slub_lock);
		if (kmem_cache_close(s)) {
			printk(KERN_ERR "SLUB %s: %s called for cache that "
				"still has objects.\n", s->name, __func__);
			dump_stack();
		}
		sysfs_slab_remove(s);
	} else
		up_write(&slub_lock);
}
