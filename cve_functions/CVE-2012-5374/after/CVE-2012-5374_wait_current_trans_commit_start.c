static void wait_current_trans_commit_start(struct btrfs_root *root,
					    struct btrfs_transaction *trans)
{
	wait_event(root->fs_info->transaction_blocked_wait, trans->in_commit);
}
