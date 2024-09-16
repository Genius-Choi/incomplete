static void *__alloc_from_contiguous(struct device *dev, size_t size,
				     pgprot_t prot, struct page **ret_page,
				     const void *caller)
{
	unsigned long order = get_order(size);
	size_t count = size >> PAGE_SHIFT;
	struct page *page;
	void *ptr;

	page = dma_alloc_from_contiguous(dev, count, order);
	if (!page)
		return NULL;

	__dma_clear_buffer(page, size);

	if (PageHighMem(page)) {
		ptr = __dma_alloc_remap(page, size, GFP_KERNEL, prot, caller);
		if (!ptr) {
			dma_release_from_contiguous(dev, page, count);
			return NULL;
		}
	} else {
		__dma_remap(page, size, prot);
		ptr = page_address(page);
	}
	*ret_page = page;
	return ptr;
}
