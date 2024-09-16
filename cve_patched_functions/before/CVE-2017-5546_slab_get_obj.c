static void *slab_get_obj(struct kmem_cache *cachep, struct page *page)
{
	void *objp;

	objp = index_to_obj(cachep, page, get_free_obj(page, page->active));
	page->active++;

#if DEBUG
	if (cachep->flags & SLAB_STORE_USER)
		set_store_user_dirty(cachep);
#endif

	return objp;
}
