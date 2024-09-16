static noinline void wait_for_commit(struct btrfs_root *root,
				    struct btrfs_transaction *commit)
{
	wait_event(commit->commit_wait, commit->commit_done);
}
