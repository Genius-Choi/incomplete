struct btrfs_trans_handle *btrfs_start_transaction(struct btrfs_root *root,
						   int num_items)
{
	return start_transaction(root, num_items, TRANS_START,
				 BTRFS_RESERVE_FLUSH_ALL);
}
