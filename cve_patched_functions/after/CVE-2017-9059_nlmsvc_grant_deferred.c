static int nlmsvc_grant_deferred(struct file_lock *fl, int result)
{
	struct nlm_block *block;
	int rc = -ENOENT;

	spin_lock(&nlm_blocked_lock);
	list_for_each_entry(block, &nlm_blocked, b_list) {
		if (nlm_compare_locks(&block->b_call->a_args.lock.fl, fl)) {
			dprintk("lockd: nlmsvc_notify_blocked block %p flags %d\n",
							block, block->b_flags);
			if (block->b_flags & B_QUEUED) {
				if (block->b_flags & B_TIMED_OUT) {
					rc = -ENOLCK;
					break;
				}
				nlmsvc_update_deferred_block(block, result);
			} else if (result == 0)
				block->b_granted = 1;

			nlmsvc_insert_block_locked(block, 0);
			svc_wake_up(block->b_daemon);
			rc = 0;
			break;
		}
	}
	spin_unlock(&nlm_blocked_lock);
	if (rc == -ENOENT)
		printk(KERN_WARNING "lockd: grant for unknown block\n");
	return rc;
}
