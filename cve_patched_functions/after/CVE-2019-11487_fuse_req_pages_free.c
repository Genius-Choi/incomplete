static void fuse_req_pages_free(struct fuse_req *req)
{
	if (req->pages != req->inline_pages)
		kfree(req->pages);
}
