xscale2pmu_write_counter(int counter, u32 val)
{
	switch (counter) {
	case XSCALE_CYCLE_COUNTER:
		asm volatile("mcr p14, 0, %0, c1, c1, 0" : : "r" (val));
		break;
	case XSCALE_COUNTER0:
		asm volatile("mcr p14, 0, %0, c0, c2, 0" : : "r" (val));
		break;
	case XSCALE_COUNTER1:
		asm volatile("mcr p14, 0, %0, c1, c2, 0" : : "r" (val));
		break;
	case XSCALE_COUNTER2:
		asm volatile("mcr p14, 0, %0, c2, c2, 0" : : "r" (val));
		break;
	case XSCALE_COUNTER3:
		asm volatile("mcr p14, 0, %0, c3, c2, 0" : : "r" (val));
		break;
	}
}
