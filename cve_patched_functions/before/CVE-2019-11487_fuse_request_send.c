void fuse_request_send(struct fuse_conn *fc, struct fuse_req *req)
{
	__set_bit(FR_ISREPLY, &req->flags);
	if (!test_bit(FR_WAITING, &req->flags)) {
		__set_bit(FR_WAITING, &req->flags);
		atomic_inc(&fc->num_waiting);
	}
	__fuse_request_send(fc, req);
}
