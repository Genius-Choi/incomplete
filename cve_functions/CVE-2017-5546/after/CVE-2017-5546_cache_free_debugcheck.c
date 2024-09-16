static void *cache_free_debugcheck(struct kmem_cache *cachep, void *objp,
				   unsigned long caller)
{
	unsigned int objnr;
	struct page *page;

	BUG_ON(virt_to_cache(objp) != cachep);

	objp -= obj_offset(cachep);
	kfree_debugcheck(objp);
	page = virt_to_head_page(objp);

	if (cachep->flags & SLAB_RED_ZONE) {
		verify_redzone_free(cachep, objp);
		*dbg_redzone1(cachep, objp) = RED_INACTIVE;
		*dbg_redzone2(cachep, objp) = RED_INACTIVE;
	}
	if (cachep->flags & SLAB_STORE_USER) {
		set_store_user_dirty(cachep);
		*dbg_userword(cachep, objp) = (void *)caller;
	}

	objnr = obj_to_index(cachep, page, objp);

	BUG_ON(objnr >= cachep->num);
	BUG_ON(objp != index_to_obj(cachep, page, objnr));

	if (cachep->flags & SLAB_POISON) {
		poison_obj(cachep, objp, POISON_FREE);
		slab_kernel_map(cachep, objp, 0, caller);
	}
	return objp;
}
