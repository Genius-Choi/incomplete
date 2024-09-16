static int __map_sg_chunk(struct device *dev, struct scatterlist *sg,
			  size_t size, dma_addr_t *handle,
			  enum dma_data_direction dir, struct dma_attrs *attrs,
			  bool is_coherent)
{
	struct dma_iommu_mapping *mapping = dev->archdata.mapping;
	dma_addr_t iova, iova_base;
	int ret = 0;
	unsigned int count;
	struct scatterlist *s;

	size = PAGE_ALIGN(size);
	*handle = DMA_ERROR_CODE;

	iova_base = iova = __alloc_iova(mapping, size);
	if (iova == DMA_ERROR_CODE)
		return -ENOMEM;

	for (count = 0, s = sg; count < (size >> PAGE_SHIFT); s = sg_next(s)) {
		phys_addr_t phys = page_to_phys(sg_page(s));
		unsigned int len = PAGE_ALIGN(s->offset + s->length);

		if (!is_coherent &&
			!dma_get_attr(DMA_ATTR_SKIP_CPU_SYNC, attrs))
			__dma_page_cpu_to_dev(sg_page(s), s->offset, s->length, dir);

		ret = iommu_map(mapping->domain, iova, phys, len, 0);
		if (ret < 0)
			goto fail;
		count += len >> PAGE_SHIFT;
		iova += len;
	}
	*handle = iova_base;

	return 0;
fail:
	iommu_unmap(mapping->domain, iova_base, count * PAGE_SIZE);
	__free_iova(mapping, iova_base, size);
	return ret;
}
