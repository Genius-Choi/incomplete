int btrfs_end_transaction_throttle(struct btrfs_trans_handle *trans,
				   struct btrfs_root *root)
{
	int ret;

	ret = __btrfs_end_transaction(trans, root, 1);
	if (ret)
		return ret;
	return 0;
}
