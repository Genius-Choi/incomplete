void unmap_hugepage_range(struct vm_area_struct *vma, unsigned long start,
			  unsigned long end, struct page *ref_page)
{
	mutex_lock(&vma->vm_file->f_mapping->i_mmap_mutex);
	__unmap_hugepage_range(vma, start, end, ref_page);
	mutex_unlock(&vma->vm_file->f_mapping->i_mmap_mutex);
}
