static int vma_has_reserves(struct vm_area_struct *vma)
{
	if (vma->vm_flags & VM_MAYSHARE)
		return 1;
	if (is_vma_resv_set(vma, HPAGE_RESV_OWNER))
		return 1;
	return 0;
}
