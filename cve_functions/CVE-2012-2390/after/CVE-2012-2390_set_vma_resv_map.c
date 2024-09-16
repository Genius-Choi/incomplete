static void set_vma_resv_map(struct vm_area_struct *vma, struct resv_map *map)
{
	VM_BUG_ON(!is_vm_hugetlb_page(vma));
	VM_BUG_ON(vma->vm_flags & VM_MAYSHARE);

	set_vma_private_data(vma, (get_vma_private_data(vma) &
				HPAGE_RESV_MASK) | (unsigned long)map);
}
