static void cleanup_transaction(struct btrfs_trans_handle *trans,
				struct btrfs_root *root, int err)
{
	struct btrfs_transaction *cur_trans = trans->transaction;

	WARN_ON(trans->use_count > 1);

	btrfs_abort_transaction(trans, root, err);

	spin_lock(&root->fs_info->trans_lock);
	list_del_init(&cur_trans->list);
	if (cur_trans == root->fs_info->running_transaction) {
		root->fs_info->running_transaction = NULL;
		root->fs_info->trans_no_join = 0;
	}
	spin_unlock(&root->fs_info->trans_lock);

	btrfs_cleanup_one_transaction(trans->transaction, root);

	put_transaction(cur_trans);
	put_transaction(cur_trans);

	trace_btrfs_transaction_commit(root);

	btrfs_scrub_continue(root);

	if (current->journal_info == trans)
		current->journal_info = NULL;

	kmem_cache_free(btrfs_trans_handle_cachep, trans);
}
