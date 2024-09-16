static int do_shrink(struct inode *inode, u64 oldsize, u64 newsize)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	int error;

	error = trunc_start(inode, oldsize, newsize);
	if (error < 0)
		return error;
	if (gfs2_is_stuffed(ip))
		return 0;

	error = trunc_dealloc(ip, newsize);
	if (error == 0)
		error = trunc_end(ip);

	return error;
}
