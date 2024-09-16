static int uio_vma_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct uio_device *idev = vma->vm_private_data;
	struct page *page;
	unsigned long offset;

	int mi = uio_find_mem_index(vma);
	if (mi < 0)
		return VM_FAULT_SIGBUS;

	/*
	 * We need to subtract mi because userspace uses offset = N*PAGE_SIZE
	 * to use mem[N].
	 */
	offset = (vmf->pgoff - mi) << PAGE_SHIFT;

	if (idev->info->mem[mi].memtype == UIO_MEM_LOGICAL)
		page = virt_to_page(idev->info->mem[mi].addr + offset);
	else
		page = vmalloc_to_page((void *)(unsigned long)idev->info->mem[mi].addr + offset);
	get_page(page);
	vmf->page = page;
	return 0;
}
