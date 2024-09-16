int gfs2_truncatei_resume(struct gfs2_inode *ip)
{
	int error;
	error = trunc_dealloc(ip, i_size_read(&ip->i_inode));
	if (!error)
		error = trunc_end(ip);
	return error;
}
