static void __fuse_put_request(struct fuse_req *req)
{
	refcount_dec(&req->count);
}
