static noinline int create_pending_snapshots(struct btrfs_trans_handle *trans,
					     struct btrfs_fs_info *fs_info)
{
	struct btrfs_pending_snapshot *pending;
	struct list_head *head = &trans->transaction->pending_snapshots;

	list_for_each_entry(pending, head, list)
		create_pending_snapshot(trans, fs_info, pending);
	return 0;
}
