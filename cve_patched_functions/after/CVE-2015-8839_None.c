int ext4_filemap_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct inode *inode = file_inode(vma->vm_file);
	int err;

	down_read(&EXT4_I(inode)->i_mmap_sem);
	err = filemap_fault(vma, vmf);
	up_read(&EXT4_I(inode)->i_mmap_sem);

	return err;
}
