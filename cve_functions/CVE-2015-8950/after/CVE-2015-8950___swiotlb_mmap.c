static int __swiotlb_mmap(struct device *dev,
			  struct vm_area_struct *vma,
			  void *cpu_addr, dma_addr_t dma_addr, size_t size,
			  struct dma_attrs *attrs)
{
	vma->vm_page_prot = __get_dma_pgprot(attrs, vma->vm_page_prot,
					     is_device_dma_coherent(dev));
	return __dma_common_mmap(dev, vma, cpu_addr, dma_addr, size);
}
