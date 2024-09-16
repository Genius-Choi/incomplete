static void swap_free_obj(struct page *page, unsigned int a, unsigned int b)
{
	swap(((freelist_idx_t *)page->freelist)[a],
		((freelist_idx_t *)page->freelist)[b]);
}
