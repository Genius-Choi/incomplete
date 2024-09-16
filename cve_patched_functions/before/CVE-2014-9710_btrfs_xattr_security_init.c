int btrfs_xattr_security_init(struct btrfs_trans_handle *trans,
			      struct inode *inode, struct inode *dir,
			      const struct qstr *qstr)
{
	return security_inode_init_security(inode, dir, qstr,
					    &btrfs_initxattrs, trans);
}
