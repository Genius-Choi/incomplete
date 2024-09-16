static int hugetlb_vmtruncate(struct inode *inode, loff_t offset)
{
	pgoff_t pgoff;
	struct address_space *mapping = inode->i_mapping;
	struct hstate *h = hstate_inode(inode);

	BUG_ON(offset & ~huge_page_mask(h));
	pgoff = offset >> PAGE_SHIFT;

	i_size_write(inode, offset);
	mutex_lock(&mapping->i_mmap_mutex);
	if (!prio_tree_empty(&mapping->i_mmap))
		hugetlb_vmtruncate_list(&mapping->i_mmap, pgoff);
	mutex_unlock(&mapping->i_mmap_mutex);
	truncate_hugepages(inode, offset);
	return 0;
}
