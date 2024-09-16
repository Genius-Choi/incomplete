static void __slab_error(const char *function, struct kmem_cache *cachep,
			char *msg)
{
	pr_err("slab error in %s(): cache `%s': %s\n",
	       function, cachep->name, msg);
	dump_stack();
	add_taint(TAINT_BAD_PAGE, LOCKDEP_NOW_UNRELIABLE);
}
