int btrfs_defrag_root(struct btrfs_root *root, int cacheonly)
{
	struct btrfs_fs_info *info = root->fs_info;
	struct btrfs_trans_handle *trans;
	int ret;

	if (xchg(&root->defrag_running, 1))
		return 0;

	while (1) {
		trans = btrfs_start_transaction(root, 0);
		if (IS_ERR(trans))
			return PTR_ERR(trans);

		ret = btrfs_defrag_leaves(trans, root, cacheonly);

		btrfs_end_transaction(trans, root);
		btrfs_btree_balance_dirty(info->tree_root);
		cond_resched();

		if (btrfs_fs_closing(root->fs_info) || ret != -EAGAIN)
			break;
	}
	root->defrag_running = 0;
	return ret;
}
