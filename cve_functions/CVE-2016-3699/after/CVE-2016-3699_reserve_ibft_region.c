static __init void reserve_ibft_region(void)
{
	unsigned long addr, size = 0;

	addr = find_ibft_region(&size);

	if (size)
		memblock_reserve(addr, size);
}
