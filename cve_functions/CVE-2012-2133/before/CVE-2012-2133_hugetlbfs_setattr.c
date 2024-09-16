static int hugetlbfs_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = dentry->d_inode;
	struct hstate *h = hstate_inode(inode);
	int error;
	unsigned int ia_valid = attr->ia_valid;

	BUG_ON(!inode);

	error = inode_change_ok(inode, attr);
	if (error)
		return error;

	if (ia_valid & ATTR_SIZE) {
		error = -EINVAL;
		if (attr->ia_size & ~huge_page_mask(h))
			return -EINVAL;
		error = hugetlb_vmtruncate(inode, attr->ia_size);
		if (error)
			return error;
	}

	setattr_copy(inode, attr);
	mark_inode_dirty(inode);
	return 0;
}
