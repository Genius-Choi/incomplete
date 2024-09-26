zalloc(unsigned long size)
{
	void *mem = xalloc(size);

	if (mem)
		memset(mem, 0, size);

	return mem;
}
