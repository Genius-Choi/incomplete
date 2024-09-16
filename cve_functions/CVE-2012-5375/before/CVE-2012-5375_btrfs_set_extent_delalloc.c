int btrfs_set_extent_delalloc(struct inode *inode, u64 start, u64 end,
			      struct extent_state **cached_state)
{
	WARN_ON((end & (PAGE_CACHE_SIZE - 1)) == 0);
	return set_extent_delalloc(&BTRFS_I(inode)->io_tree, start, end,
				   cached_state, GFP_NOFS);
}
