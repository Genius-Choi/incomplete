static int should_end_transaction(struct btrfs_trans_handle *trans,
				  struct btrfs_root *root)
{
	int ret;

	ret = btrfs_block_rsv_check(root, &root->fs_info->global_block_rsv, 5);
	return ret ? 1 : 0;
}
