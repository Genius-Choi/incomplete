unsigned find_get_pages_contig(struct address_space *mapping, pgoff_t index,
			       unsigned int nr_pages, struct page **pages)
{
	unsigned int i;
	unsigned int ret;

	read_lock_irq(&mapping->tree_lock);
	ret = radix_tree_gang_lookup(&mapping->page_tree,
				(void **)pages, index, nr_pages);
	for (i = 0; i < ret; i++) {
		if (pages[i]->mapping == NULL || pages[i]->index != index)
			break;

		page_cache_get(pages[i]);
		index++;
	}
	read_unlock_irq(&mapping->tree_lock);
	return i;
}
