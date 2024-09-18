armv6_pmcr_counter_has_overflowed(unsigned long pmcr,
				  enum armv6_counters counter)
{
	int ret = 0;

	if (ARMV6_CYCLE_COUNTER == counter)
		ret = pmcr & ARMV6_PMCR_CCOUNT_OVERFLOW;
	else if (ARMV6_COUNTER0 == counter)
		ret = pmcr & ARMV6_PMCR_COUNT0_OVERFLOW;
	else if (ARMV6_COUNTER1 == counter)
		ret = pmcr & ARMV6_PMCR_COUNT1_OVERFLOW;
	else
		WARN_ONCE(1, "invalid counter number (%d)\n", counter);

	return ret;
}
