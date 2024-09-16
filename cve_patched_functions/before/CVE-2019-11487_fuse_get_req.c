struct fuse_req *fuse_get_req(struct fuse_conn *fc, unsigned npages)
{
	return __fuse_get_req(fc, npages, false);
}
