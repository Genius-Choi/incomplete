static void kmem_cache_release(struct kobject *kobj)
{
	struct kmem_cache *s = to_slab(kobj);

	kfree(s);
}
