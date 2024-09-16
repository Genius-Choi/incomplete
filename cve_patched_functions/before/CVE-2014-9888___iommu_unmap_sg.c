static void __iommu_unmap_sg(struct device *dev, struct scatterlist *sg,
		int nents, enum dma_data_direction dir, struct dma_attrs *attrs,
		bool is_coherent)
{
	struct scatterlist *s;
	int i;

	for_each_sg(sg, s, nents, i) {
		if (sg_dma_len(s))
			__iommu_remove_mapping(dev, sg_dma_address(s),
					       sg_dma_len(s));
		if (!is_coherent &&
		    !dma_get_attr(DMA_ATTR_SKIP_CPU_SYNC, attrs))
			__dma_page_dev_to_cpu(sg_page(s), s->offset,
					      s->length, dir);
	}
}
