static bool __in_atomic_pool(void *start, size_t size)
{
	struct dma_pool *pool = &atomic_pool;
	void *end = start + size;
	void *pool_start = pool->vaddr;
	void *pool_end = pool->vaddr + pool->size;

	if (start < pool_start || start >= pool_end)
		return false;

	if (end <= pool_end)
		return true;

	WARN(1, "Wrong coherent size(%p-%p) from atomic pool(%p-%p)\n",
	     start, end - 1, pool_start, pool_end - 1);

	return false;
}
