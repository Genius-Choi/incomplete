armv6_pmcr_write(unsigned long val)
{
	asm volatile("mcr   p15, 0, %0, c15, c12, 0" : : "r"(val));
}
