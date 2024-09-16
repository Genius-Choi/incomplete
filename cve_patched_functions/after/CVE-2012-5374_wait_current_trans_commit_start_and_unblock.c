static void wait_current_trans_commit_start_and_unblock(struct btrfs_root *root,
					 struct btrfs_transaction *trans)
{
	wait_event(root->fs_info->transaction_wait,
		   trans->commit_done || (trans->in_commit && !trans->blocked));
}
