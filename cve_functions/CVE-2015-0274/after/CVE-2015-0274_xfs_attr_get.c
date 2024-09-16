xfs_attr_get(
	xfs_inode_t	*ip,
	const unsigned char *name,
	unsigned char	*value,
	int		*valuelenp,
	int		flags)
{
	int		error;
	struct xfs_name	xname;
	uint		lock_mode;

	XFS_STATS_INC(xs_attr_get);

	if (XFS_FORCED_SHUTDOWN(ip->i_mount))
		return(EIO);

	error = xfs_attr_name_to_xname(&xname, name);
	if (error)
		return error;

	lock_mode = xfs_ilock_attr_map_shared(ip);
	error = xfs_attr_get_int(ip, &xname, value, valuelenp, flags);
	xfs_iunlock(ip, lock_mode);
	return(error);
}
