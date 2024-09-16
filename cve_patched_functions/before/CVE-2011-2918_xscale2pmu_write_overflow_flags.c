xscale2pmu_write_overflow_flags(u32 val)
{
	asm volatile("mcr p14, 0, %0, c5, c1, 0" : : "r" (val));
}
