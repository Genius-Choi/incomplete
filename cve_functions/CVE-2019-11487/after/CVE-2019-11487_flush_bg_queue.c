static void flush_bg_queue(struct fuse_conn *fc)
{
	struct fuse_iqueue *fiq = &fc->iq;

	while (fc->active_background < fc->max_background &&
	       !list_empty(&fc->bg_queue)) {
		struct fuse_req *req;

		req = list_first_entry(&fc->bg_queue, struct fuse_req, list);
		list_del(&req->list);
		fc->active_background++;
		spin_lock(&fiq->waitq.lock);
		req->in.h.unique = fuse_get_unique(fiq);
		queue_request(fiq, req);
		spin_unlock(&fiq->waitq.lock);
	}
}
