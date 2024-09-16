xscale2pmu_read_counter(int counter)
{
	u32 val = 0;

	switch (counter) {
	case XSCALE_CYCLE_COUNTER:
		asm volatile("mrc p14, 0, %0, c1, c1, 0" : "=r" (val));
		break;
	case XSCALE_COUNTER0:
		asm volatile("mrc p14, 0, %0, c0, c2, 0" : "=r" (val));
		break;
	case XSCALE_COUNTER1:
		asm volatile("mrc p14, 0, %0, c1, c2, 0" : "=r" (val));
		break;
	case XSCALE_COUNTER2:
		asm volatile("mrc p14, 0, %0, c2, c2, 0" : "=r" (val));
		break;
	case XSCALE_COUNTER3:
		asm volatile("mrc p14, 0, %0, c3, c2, 0" : "=r" (val));
		break;
	}

	return val;
}
