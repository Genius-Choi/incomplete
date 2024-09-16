static void hugetlbfs_evict_inode(struct inode *inode)
{
	truncate_hugepages(inode, 0);
	end_writeback(inode);
}
