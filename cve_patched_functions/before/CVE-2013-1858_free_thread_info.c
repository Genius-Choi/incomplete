static void free_thread_info(struct thread_info *ti)
{
	kmem_cache_free(thread_info_cache, ti);
}
