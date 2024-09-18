armv6pmu_read_counter(int counter)
{
	unsigned long value = 0;

	if (ARMV6_CYCLE_COUNTER == counter)
		asm volatile("mrc   p15, 0, %0, c15, c12, 1" : "=r"(value));
	else if (ARMV6_COUNTER0 == counter)
		asm volatile("mrc   p15, 0, %0, c15, c12, 2" : "=r"(value));
	else if (ARMV6_COUNTER1 == counter)
		asm volatile("mrc   p15, 0, %0, c15, c12, 3" : "=r"(value));
	else
		WARN_ONCE(1, "invalid counter number (%d)\n", counter);

	return value;
}
