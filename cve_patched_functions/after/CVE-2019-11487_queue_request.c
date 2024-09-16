static void queue_request(struct fuse_iqueue *fiq, struct fuse_req *req)
{
	req->in.h.len = sizeof(struct fuse_in_header) +
		len_args(req->in.numargs, (struct fuse_arg *) req->in.args);
	list_add_tail(&req->list, &fiq->pending);
	wake_up_locked(&fiq->waitq);
	kill_fasync(&fiq->fasync, SIGIO, POLL_IN);
}
