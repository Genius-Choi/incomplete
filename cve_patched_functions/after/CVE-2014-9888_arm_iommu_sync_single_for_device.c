static void arm_iommu_sync_single_for_device(struct device *dev,
		dma_addr_t handle, size_t size, enum dma_data_direction dir)
{
	struct dma_iommu_mapping *mapping = dev->archdata.mapping;
	dma_addr_t iova = handle & PAGE_MASK;
	struct page *page = phys_to_page(iommu_iova_to_phys(mapping->domain, iova));
	unsigned int offset = handle & ~PAGE_MASK;

	if (!iova)
		return;

	__dma_page_cpu_to_dev(page, offset, size, dir);
}
