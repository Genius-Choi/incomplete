static int btrfs_writepage_end_io_hook(struct page *page, u64 start, u64 end,
				struct extent_state *state, int uptodate)
{
	struct inode *inode = page->mapping->host;
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_ordered_extent *ordered_extent = NULL;
	struct btrfs_workers *workers;

	trace_btrfs_writepage_end_io_hook(page, start, end, uptodate);

	ClearPagePrivate2(page);
	if (!btrfs_dec_test_ordered_pending(inode, &ordered_extent, start,
					    end - start + 1, uptodate))
		return 0;

	ordered_extent->work.func = finish_ordered_fn;
	ordered_extent->work.flags = 0;

	if (btrfs_is_free_space_inode(inode))
		workers = &root->fs_info->endio_freespace_worker;
	else
		workers = &root->fs_info->endio_write_workers;
	btrfs_queue_worker(workers, &ordered_extent->work);

	return 0;
}
