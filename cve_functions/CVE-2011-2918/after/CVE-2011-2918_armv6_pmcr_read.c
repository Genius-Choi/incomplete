armv6_pmcr_read(void)
{
	u32 val;
	asm volatile("mrc   p15, 0, %0, c15, c12, 0" : "=r"(val));
	return val;
}
