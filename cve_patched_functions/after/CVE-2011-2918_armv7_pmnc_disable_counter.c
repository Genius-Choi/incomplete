static inline u32 armv7_pmnc_disable_counter(unsigned int idx)
{
	u32 val;


	if ((idx != ARMV7_CYCLE_COUNTER) &&
	    ((idx < ARMV7_COUNTER0) || (idx > ARMV7_COUNTER_LAST))) {
		pr_err("CPU%u disabling wrong PMNC counter"
			" %d\n", smp_processor_id(), idx);
		return -1;
	}

	if (idx == ARMV7_CYCLE_COUNTER)
		val = ARMV7_CNTENC_C;
	else
		val = ARMV7_CNTENC_P(idx);

	asm volatile("mcr p15, 0, %0, c9, c12, 2" : : "r" (val));

	return idx;
}
