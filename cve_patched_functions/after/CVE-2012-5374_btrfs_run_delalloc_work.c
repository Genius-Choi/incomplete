static void btrfs_run_delalloc_work(struct btrfs_work *work)
{
	struct btrfs_delalloc_work *delalloc_work;

	delalloc_work = container_of(work, struct btrfs_delalloc_work,
				     work);
	if (delalloc_work->wait)
		btrfs_wait_ordered_range(delalloc_work->inode, 0, (u64)-1);
	else
		filemap_flush(delalloc_work->inode->i_mapping);

	if (delalloc_work->delay_iput)
		btrfs_add_delayed_iput(delalloc_work->inode);
	else
		iput(delalloc_work->inode);
	complete(&delalloc_work->completion);
}
