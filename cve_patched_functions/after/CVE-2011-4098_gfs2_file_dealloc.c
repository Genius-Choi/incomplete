int gfs2_file_dealloc(struct gfs2_inode *ip)
{
	return trunc_dealloc(ip, 0);
}
