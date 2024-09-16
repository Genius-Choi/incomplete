int btrfs_end_transaction_dmeta(struct btrfs_trans_handle *trans,
				struct btrfs_root *root)
{
	return __btrfs_end_transaction(trans, root, 1);
}
