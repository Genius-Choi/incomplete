static void ovl_remove_opaque(struct dentry *upperdentry)
{
	int err;

	err = ovl_do_removexattr(upperdentry, OVL_XATTR_OPAQUE);
	if (err) {
		pr_warn("overlayfs: failed to remove opaque from '%s' (%i)\n",
			upperdentry->d_name.name, err);
	}
}
