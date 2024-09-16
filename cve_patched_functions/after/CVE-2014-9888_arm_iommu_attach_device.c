int arm_iommu_attach_device(struct device *dev,
			    struct dma_iommu_mapping *mapping)
{
	int err;

	err = iommu_attach_device(mapping->domain, dev);
	if (err)
		return err;

	kref_get(&mapping->kref);
	dev->archdata.mapping = mapping;
	set_dma_ops(dev, &iommu_ops);

	pr_debug("Attached IOMMU controller to %s device.\n", dev_name(dev));
	return 0;
}
