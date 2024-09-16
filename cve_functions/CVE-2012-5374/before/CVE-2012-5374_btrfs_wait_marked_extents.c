int btrfs_wait_marked_extents(struct btrfs_root *root,
			      struct extent_io_tree *dirty_pages, int mark)
{
	int err = 0;
	int werr = 0;
	struct address_space *mapping = root->fs_info->btree_inode->i_mapping;
	struct extent_state *cached_state = NULL;
	u64 start = 0;
	u64 end;

	while (!find_first_extent_bit(dirty_pages, start, &start, &end,
				      EXTENT_NEED_WAIT, &cached_state)) {
		clear_extent_bit(dirty_pages, start, end, EXTENT_NEED_WAIT,
				 0, 0, &cached_state, GFP_NOFS);
		err = filemap_fdatawait_range(mapping, start, end);
		if (err)
			werr = err;
		cond_resched();
		start = end + 1;
	}
	if (err)
		werr = err;
	return werr;
}
