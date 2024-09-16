void gfs2_set_inode_flags(struct inode *inode)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	unsigned int flags = inode->i_flags;

	flags &= ~(S_SYNC|S_APPEND|S_IMMUTABLE|S_NOATIME|S_DIRSYNC|S_NOSEC);
	if ((ip->i_eattr == 0) && !is_sxid(inode->i_mode))
		inode->i_flags |= S_NOSEC;
	if (ip->i_diskflags & GFS2_DIF_IMMUTABLE)
		flags |= S_IMMUTABLE;
	if (ip->i_diskflags & GFS2_DIF_APPENDONLY)
		flags |= S_APPEND;
	if (ip->i_diskflags & GFS2_DIF_NOATIME)
		flags |= S_NOATIME;
	if (ip->i_diskflags & GFS2_DIF_SYNC)
		flags |= S_SYNC;
	inode->i_flags = flags;
}
