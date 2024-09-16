void fuse_queue_forget(struct fuse_conn *fc, struct fuse_forget_link *forget,
		       u64 nodeid, u64 nlookup)
{
	struct fuse_iqueue *fiq = &fc->iq;

	forget->forget_one.nodeid = nodeid;
	forget->forget_one.nlookup = nlookup;

	spin_lock(&fiq->waitq.lock);
	if (fiq->connected) {
		fiq->forget_list_tail->next = forget;
		fiq->forget_list_tail = forget;
		wake_up_locked(&fiq->waitq);
		kill_fasync(&fiq->fasync, SIGIO, POLL_IN);
	} else {
		kfree(forget);
	}
	spin_unlock(&fiq->waitq.lock);
}
