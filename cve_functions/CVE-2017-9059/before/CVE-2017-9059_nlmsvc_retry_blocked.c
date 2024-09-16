nlmsvc_retry_blocked(void)
{
	unsigned long	timeout = MAX_SCHEDULE_TIMEOUT;
	struct nlm_block *block;

	spin_lock(&nlm_blocked_lock);
	while (!list_empty(&nlm_blocked) && !kthread_should_stop()) {
		block = list_entry(nlm_blocked.next, struct nlm_block, b_list);

		if (block->b_when == NLM_NEVER)
			break;
		if (time_after(block->b_when, jiffies)) {
			timeout = block->b_when - jiffies;
			break;
		}
		spin_unlock(&nlm_blocked_lock);

		dprintk("nlmsvc_retry_blocked(%p, when=%ld)\n",
			block, block->b_when);
		if (block->b_flags & B_QUEUED) {
			dprintk("nlmsvc_retry_blocked delete block (%p, granted=%d, flags=%d)\n",
				block, block->b_granted, block->b_flags);
			retry_deferred_block(block);
		} else
			nlmsvc_grant_blocked(block);
		spin_lock(&nlm_blocked_lock);
	}
	spin_unlock(&nlm_blocked_lock);

	return timeout;
}
