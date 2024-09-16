void reset_vma_resv_huge_pages(struct vm_area_struct *vma)
{
	VM_BUG_ON(!is_vm_hugetlb_page(vma));
	if (!(vma->vm_flags & VM_MAYSHARE))
		vma->vm_private_data = (void *)0;
}
