int kmem_ptr_validate(struct kmem_cache *s, const void *object)
{
	struct page *page;

	page = get_object_page(object);

	if (!page || s != page->slab)
		/* No slab or wrong slab */
		return 0;

	if (!check_valid_pointer(s, page, object))
		return 0;

	/*
	 * We could also check if the object is on the slabs freelist.
	 * But this would be too expensive and it seems that the main
	 * purpose of kmem_ptr_valid() is to check if the object belongs
	 * to a certain slab.
	 */
	return 1;
}
