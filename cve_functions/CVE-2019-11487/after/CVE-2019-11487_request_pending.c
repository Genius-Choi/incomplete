static int request_pending(struct fuse_iqueue *fiq)
{
	return !list_empty(&fiq->pending) || !list_empty(&fiq->interrupts) ||
		forget_pending(fiq);
}
