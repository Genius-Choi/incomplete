xfs_dentry_mode_to_name(
	struct xfs_name	*namep,
	struct dentry	*dentry,
	int		mode)
{
	namep->name = dentry->d_name.name;
	namep->len = dentry->d_name.len;
	namep->type = xfs_mode_to_ftype(mode);

	if (unlikely(namep->type == XFS_DIR3_FT_UNKNOWN))
		return -EFSCORRUPTED;

	return 0;
}
