void __fuse_get_request(struct fuse_req *req)
{
	refcount_inc(&req->count);
}
