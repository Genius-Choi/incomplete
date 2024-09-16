void __cpuinit set_uncached_handler(unsigned long offset, void *addr,
	unsigned long size)
{
	unsigned long uncached_ebase = CKSEG1ADDR(ebase);

	if (!addr)
		panic(panic_null_cerr);

	memcpy((void *)(uncached_ebase + offset), addr, size);
}
