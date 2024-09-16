void arm_dma_free(struct device *dev, size_t size, void *cpu_addr,
		  dma_addr_t handle, struct dma_attrs *attrs)
{
	__arm_dma_free(dev, size, cpu_addr, handle, attrs, false);
}
