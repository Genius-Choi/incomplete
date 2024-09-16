static struct page **__iommu_get_pages(void *cpu_addr, struct dma_attrs *attrs)
{
	struct vm_struct *area;

	if (__in_atomic_pool(cpu_addr, PAGE_SIZE))
		return __atomic_get_pages(cpu_addr);

	if (dma_get_attr(DMA_ATTR_NO_KERNEL_MAPPING, attrs))
		return cpu_addr;

	area = find_vm_area(cpu_addr);
	if (area && (area->flags & VM_ARM_DMA_CONSISTENT))
		return area->pages;
	return NULL;
}
