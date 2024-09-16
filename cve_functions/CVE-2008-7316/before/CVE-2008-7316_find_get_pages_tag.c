unsigned find_get_pages_tag(struct address_space *mapping, pgoff_t *index,
			int tag, unsigned int nr_pages, struct page **pages)
{
	unsigned int i;
	unsigned int ret;

	read_lock_irq(&mapping->tree_lock);
	ret = radix_tree_gang_lookup_tag(&mapping->page_tree,
				(void **)pages, *index, nr_pages, tag);
	for (i = 0; i < ret; i++)
		page_cache_get(pages[i]);
	if (ret)
		*index = pages[ret - 1]->index + 1;
	read_unlock_irq(&mapping->tree_lock);
	return ret;
}
