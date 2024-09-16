int cifs_file_strict_mmap(struct file *file, struct vm_area_struct *vma)
{
	int rc, xid;
	struct inode *inode = file_inode(file);

	xid = get_xid();

	if (!CIFS_CACHE_READ(CIFS_I(inode))) {
		rc = cifs_invalidate_mapping(inode);
		if (rc)
			return rc;
	}

	rc = generic_file_mmap(file, vma);
	if (rc == 0)
		vma->vm_ops = &cifs_file_vm_ops;
	free_xid(xid);
	return rc;
}
