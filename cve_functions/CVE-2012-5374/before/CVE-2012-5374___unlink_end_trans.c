static void __unlink_end_trans(struct btrfs_trans_handle *trans,
			       struct btrfs_root *root)
{
	if (trans->block_rsv->type == BTRFS_BLOCK_RSV_GLOBAL) {
		btrfs_block_rsv_release(root, trans->block_rsv,
					trans->bytes_reserved);
		trans->block_rsv = &root->fs_info->trans_block_rsv;
		BUG_ON(!root->fs_info->enospc_unlink);
		root->fs_info->enospc_unlink = 0;
	}
	btrfs_end_transaction(trans, root);
}
