xscale2_pmnc_counter_has_overflowed(unsigned long of_flags,
					enum xscale_counters counter)
{
	int ret = 0;

	switch (counter) {
	case XSCALE_CYCLE_COUNTER:
		ret = of_flags & XSCALE2_CCOUNT_OVERFLOW;
		break;
	case XSCALE_COUNTER0:
		ret = of_flags & XSCALE2_COUNT0_OVERFLOW;
		break;
	case XSCALE_COUNTER1:
		ret = of_flags & XSCALE2_COUNT1_OVERFLOW;
		break;
	case XSCALE_COUNTER2:
		ret = of_flags & XSCALE2_COUNT2_OVERFLOW;
		break;
	case XSCALE_COUNTER3:
		ret = of_flags & XSCALE2_COUNT3_OVERFLOW;
		break;
	default:
		WARN_ONCE(1, "invalid counter number (%d)\n", counter);
	}

	return ret;
}
