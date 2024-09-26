static inline struct hugepage_subpool *subpool_vma(struct vm_area_struct *vma)
{
	return subpool_inode(vma->vm_file->f_dentry->d_inode);
}
