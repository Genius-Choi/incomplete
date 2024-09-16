bool fuse_request_queue_background(struct fuse_conn *fc, struct fuse_req *req)
{
	bool queued = false;

	WARN_ON(!test_bit(FR_BACKGROUND, &req->flags));
	if (!test_bit(FR_WAITING, &req->flags)) {
		__set_bit(FR_WAITING, &req->flags);
		atomic_inc(&fc->num_waiting);
	}
	__set_bit(FR_ISREPLY, &req->flags);
	spin_lock(&fc->bg_lock);
	if (likely(fc->connected)) {
		fc->num_background++;
		if (fc->num_background == fc->max_background)
			fc->blocked = 1;
		if (fc->num_background == fc->congestion_threshold && fc->sb) {
			set_bdi_congested(fc->sb->s_bdi, BLK_RW_SYNC);
			set_bdi_congested(fc->sb->s_bdi, BLK_RW_ASYNC);
		}
		list_add_tail(&req->list, &fc->bg_queue);
		flush_bg_queue(fc);
		queued = true;
	}
	spin_unlock(&fc->bg_lock);

	return queued;
}
