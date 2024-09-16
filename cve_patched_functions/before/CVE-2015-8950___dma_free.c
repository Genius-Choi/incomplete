static void __dma_free(struct device *dev, size_t size,
		       void *vaddr, dma_addr_t dma_handle,
		       struct dma_attrs *attrs)
{
	void *swiotlb_addr = phys_to_virt(dma_to_phys(dev, dma_handle));

	if (!is_device_dma_coherent(dev)) {
		if (__free_from_pool(vaddr, size))
			return;
		vunmap(vaddr);
	}
	__dma_free_coherent(dev, size, swiotlb_addr, dma_handle, attrs);
}
