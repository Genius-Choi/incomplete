int add_to_page_cache(struct page *page, struct address_space *mapping,
		pgoff_t offset, gfp_t gfp_mask)
{
	int error = radix_tree_preload(gfp_mask & ~__GFP_HIGHMEM);

	if (error == 0) {
		write_lock_irq(&mapping->tree_lock);
		error = radix_tree_insert(&mapping->page_tree, offset, page);
		if (!error) {
			page_cache_get(page);
			SetPageLocked(page);
			page->mapping = mapping;
			page->index = offset;
			mapping->nrpages++;
			__inc_zone_page_state(page, NR_FILE_PAGES);
		}
		write_unlock_irq(&mapping->tree_lock);
		radix_tree_preload_end();
	}
	return error;
}
