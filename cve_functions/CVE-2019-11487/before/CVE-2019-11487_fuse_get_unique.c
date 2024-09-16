static u64 fuse_get_unique(struct fuse_iqueue *fiq)
{
	fiq->reqctr += FUSE_REQ_ID_STEP;
	return fiq->reqctr;
}
