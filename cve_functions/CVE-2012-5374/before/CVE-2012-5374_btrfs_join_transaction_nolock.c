struct btrfs_trans_handle *btrfs_join_transaction_nolock(struct btrfs_root *root)
{
	return start_transaction(root, 0, TRANS_JOIN_NOLOCK, 0);
}
