void evm_inode_post_setattr(struct dentry *dentry, int ia_valid)
{
	if (!evm_initialized)
		return;

	if (ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID))
		evm_update_evmxattr(dentry, NULL, NULL, 0);
}
