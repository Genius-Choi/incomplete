static noinline int cow_file_range(struct inode *inode,
				   struct page *locked_page,
				   u64 start, u64 end, int *page_started,
				   unsigned long *nr_written,
				   int unlock)
{
	struct btrfs_trans_handle *trans;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	int ret;

	trans = btrfs_join_transaction(root);
	if (IS_ERR(trans)) {
		extent_clear_unlock_delalloc(inode,
			     &BTRFS_I(inode)->io_tree,
			     start, end, locked_page,
			     EXTENT_CLEAR_UNLOCK_PAGE |
			     EXTENT_CLEAR_UNLOCK |
			     EXTENT_CLEAR_DELALLOC |
			     EXTENT_CLEAR_DIRTY |
			     EXTENT_SET_WRITEBACK |
			     EXTENT_END_WRITEBACK);
		return PTR_ERR(trans);
	}
	trans->block_rsv = &root->fs_info->delalloc_block_rsv;

	ret = __cow_file_range(trans, inode, root, locked_page, start, end,
			       page_started, nr_written, unlock);

	btrfs_end_transaction(trans, root);

	return ret;
}
