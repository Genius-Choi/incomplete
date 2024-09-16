void arm_iommu_detach_device(struct device *dev)
{
	struct dma_iommu_mapping *mapping;

	mapping = to_dma_iommu_mapping(dev);
	if (!mapping) {
		dev_warn(dev, "Not attached\n");
		return;
	}

	iommu_detach_device(mapping->domain, dev);
	kref_put(&mapping->kref, release_iommu_mapping);
	dev->archdata.mapping = NULL;
	set_dma_ops(dev, NULL);

	pr_debug("Detached IOMMU controller from %s device.\n", dev_name(dev));
}
