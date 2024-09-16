xfs_attr_remove(
	xfs_inode_t	*dp,
	const unsigned char *name,
	int		flags)
{
	int		error;
	struct xfs_name	xname;

	XFS_STATS_INC(xs_attr_remove);

	if (XFS_FORCED_SHUTDOWN(dp->i_mount))
		return (EIO);

	error = xfs_attr_name_to_xname(&xname, name);
	if (error)
		return error;

	xfs_ilock(dp, XFS_ILOCK_SHARED);
	if (!xfs_inode_hasattr(dp)) {
		xfs_iunlock(dp, XFS_ILOCK_SHARED);
		return XFS_ERROR(ENOATTR);
	}
	xfs_iunlock(dp, XFS_ILOCK_SHARED);

	return xfs_attr_remove_int(dp, &xname, flags);
}
