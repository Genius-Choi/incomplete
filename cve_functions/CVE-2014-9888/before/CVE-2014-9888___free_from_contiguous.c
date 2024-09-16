static void __free_from_contiguous(struct device *dev, struct page *page,
				   void *cpu_addr, size_t size)
{
	if (PageHighMem(page))
		__dma_free_remap(cpu_addr, size);
	else
		__dma_remap(page, size, pgprot_kernel);
	dma_release_from_contiguous(dev, page, size >> PAGE_SHIFT);
}
