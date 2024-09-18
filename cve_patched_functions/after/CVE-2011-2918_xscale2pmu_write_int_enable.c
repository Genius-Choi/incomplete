xscale2pmu_write_int_enable(u32 val)
{
	asm volatile("mcr p14, 0, %0, c4, c1, 0" : : "r" (val));
}
