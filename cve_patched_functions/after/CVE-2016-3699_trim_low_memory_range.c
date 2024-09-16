static void __init trim_low_memory_range(void)
{
	memblock_reserve(0, ALIGN(reserve_low, PAGE_SIZE));
}
