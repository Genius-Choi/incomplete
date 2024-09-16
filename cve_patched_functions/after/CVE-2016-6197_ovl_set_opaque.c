static int ovl_set_opaque(struct dentry *upperdentry)
{
	return ovl_do_setxattr(upperdentry, OVL_XATTR_OPAQUE, "y", 1, 0);
}
