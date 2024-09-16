static void free_alien_cache(struct alien_cache **alc_ptr)
{
	int i;

	if (!alc_ptr)
		return;
	for_each_node(i)
	    kfree(alc_ptr[i]);
	kfree(alc_ptr);
}
