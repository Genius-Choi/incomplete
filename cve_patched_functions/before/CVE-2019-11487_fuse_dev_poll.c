static __poll_t fuse_dev_poll(struct file *file, poll_table *wait)
{
	__poll_t mask = EPOLLOUT | EPOLLWRNORM;
	struct fuse_iqueue *fiq;
	struct fuse_dev *fud = fuse_get_dev(file);

	if (!fud)
		return EPOLLERR;

	fiq = &fud->fc->iq;
	poll_wait(file, &fiq->waitq, wait);

	spin_lock(&fiq->waitq.lock);
	if (!fiq->connected)
		mask = EPOLLERR;
	else if (request_pending(fiq))
		mask |= EPOLLIN | EPOLLRDNORM;
	spin_unlock(&fiq->waitq.lock);

	return mask;
}
