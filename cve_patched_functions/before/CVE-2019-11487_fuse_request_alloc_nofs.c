struct fuse_req *fuse_request_alloc_nofs(unsigned npages)
{
	return __fuse_request_alloc(npages, GFP_NOFS);
}
