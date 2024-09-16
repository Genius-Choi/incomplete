noinline int btrfs_cow_block(struct btrfs_trans_handle *trans,
		    struct btrfs_root *root, struct extent_buffer *buf,
		    struct extent_buffer *parent, int parent_slot,
		    struct extent_buffer **cow_ret)
{
	u64 search_start;
	int ret;

	if (trans->transaction != root->fs_info->running_transaction)
		WARN(1, KERN_CRIT "trans %llu running %llu\n",
		       trans->transid,
		       root->fs_info->running_transaction->transid);

	if (trans->transid != root->fs_info->generation)
		WARN(1, KERN_CRIT "trans %llu running %llu\n",
		       trans->transid, root->fs_info->generation);

	if (!should_cow_block(trans, root, buf)) {
		*cow_ret = buf;
		return 0;
	}

	search_start = buf->start & ~((u64)(1024 * 1024 * 1024) - 1);

	if (parent)
		btrfs_set_lock_blocking(parent);
	btrfs_set_lock_blocking(buf);

	ret = __btrfs_cow_block(trans, root, buf, parent,
				 parent_slot, cow_ret, search_start, 0);

	trace_btrfs_cow_block(root, buf, *cow_ret);

	return ret;
}
