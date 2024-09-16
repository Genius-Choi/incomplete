xscale1pmu_read_pmnc(void)
{
	u32 val;
	asm volatile("mrc p14, 0, %0, c0, c0, 0" : "=r" (val));
	return val;
}
