static struct resource *additional_memory_resource(phys_addr_t size)
{
	struct resource *res;
	int ret;

	res = kzalloc(sizeof(*res), GFP_KERNEL);
	if (!res)
		return NULL;

	res->name = "System RAM";
	res->flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;

	ret = allocate_resource(&iomem_resource, res,
				size, 0, -1,
				PAGES_PER_SECTION * PAGE_SIZE, NULL, NULL);
	if (ret < 0) {
		pr_err("Cannot allocate new System RAM resource\n");
		kfree(res);
		return NULL;
	}

#ifdef CONFIG_SPARSEMEM
	{
		unsigned long limit = 1UL << (MAX_PHYSMEM_BITS - PAGE_SHIFT);
		unsigned long pfn = res->start >> PAGE_SHIFT;

		if (pfn > limit) {
			pr_err("New System RAM resource outside addressable RAM (%lu > %lu)\n",
			       pfn, limit);
			release_memory_resource(res);
			return NULL;
		}
	}
#endif

	return res;
}
