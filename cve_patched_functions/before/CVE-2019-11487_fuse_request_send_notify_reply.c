static int fuse_request_send_notify_reply(struct fuse_conn *fc,
					  struct fuse_req *req, u64 unique)
{
	int err = -ENODEV;
	struct fuse_iqueue *fiq = &fc->iq;

	__clear_bit(FR_ISREPLY, &req->flags);
	req->in.h.unique = unique;
	spin_lock(&fiq->waitq.lock);
	if (fiq->connected) {
		queue_request(fiq, req);
		err = 0;
	}
	spin_unlock(&fiq->waitq.lock);

	return err;
}
