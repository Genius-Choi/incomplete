void fuse_request_free(struct fuse_req *req)
{
	fuse_req_pages_free(req);
	kmem_cache_free(fuse_req_cachep, req);
}
