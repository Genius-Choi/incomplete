static int is_vma_resv_set(struct vm_area_struct *vma, unsigned long flag)
{
	VM_BUG_ON(!is_vm_hugetlb_page(vma));

	return (get_vma_private_data(vma) & flag) != 0;
}
