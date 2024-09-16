static void *__iommu_alloc_atomic(struct device *dev, size_t size,
				  dma_addr_t *handle)
{
	struct page *page;
	void *addr;

	addr = __alloc_from_pool(size, &page);
	if (!addr)
		return NULL;

	*handle = __iommu_create_mapping(dev, &page, size);
	if (*handle == DMA_ERROR_CODE)
		goto err_mapping;

	return addr;

err_mapping:
	__free_from_pool(addr, size);
	return NULL;
}
