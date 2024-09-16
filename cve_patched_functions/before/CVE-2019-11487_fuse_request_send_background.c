void fuse_request_send_background(struct fuse_conn *fc, struct fuse_req *req)
{
	WARN_ON(!req->end);
	if (!fuse_request_queue_background(fc, req)) {
		req->out.h.error = -ENOTCONN;
		req->end(fc, req);
		fuse_put_request(fc, req);
	}
}
