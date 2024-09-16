static int rmap_walk_file(struct page *page, struct rmap_walk_control *rwc)
{
	struct address_space *mapping = page->mapping;
	pgoff_t pgoff = page->index << compound_order(page);
	struct vm_area_struct *vma;
	int ret = SWAP_AGAIN;

	/*
	 * The page lock not only makes sure that page->mapping cannot
	 * suddenly be NULLified by truncation, it makes sure that the
	 * structure at mapping cannot be freed and reused yet,
	 * so we can safely take mapping->i_mmap_mutex.
	 */
	VM_BUG_ON(!PageLocked(page));

	if (!mapping)
		return ret;
	mutex_lock(&mapping->i_mmap_mutex);
	vma_interval_tree_foreach(vma, &mapping->i_mmap, pgoff, pgoff) {
		unsigned long address = vma_address(page, vma);

		if (rwc->invalid_vma && rwc->invalid_vma(vma, rwc->arg))
			continue;

		ret = rwc->rmap_one(page, vma, address, rwc->arg);
		if (ret != SWAP_AGAIN)
			goto done;
		if (rwc->done && rwc->done(page))
			goto done;
	}

	if (!rwc->file_nonlinear)
		goto done;

	if (list_empty(&mapping->i_mmap_nonlinear))
		goto done;

	ret = rwc->file_nonlinear(page, mapping, rwc->arg);

done:
	mutex_unlock(&mapping->i_mmap_mutex);
	return ret;
}
