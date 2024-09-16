xscale2pmu_write_event_select(u32 val)
{
	asm volatile("mcr p14, 0, %0, c8, c1, 0" : : "r"(val));
}
