xscale2pmu_read_overflow_flags(void)
{
	u32 val;
	asm volatile("mrc p14, 0, %0, c5, c1, 0" : "=r" (val));
	return val;
}
