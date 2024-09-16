static inline u32 armv7_pmnc_enable_intens(unsigned int idx)
{
	u32 val;

	if ((idx != ARMV7_CYCLE_COUNTER) &&
	    ((idx < ARMV7_COUNTER0) || (idx > ARMV7_COUNTER_LAST))) {
		pr_err("CPU%u enabling wrong PMNC counter"
			" interrupt enable %d\n", smp_processor_id(), idx);
		return -1;
	}

	if (idx == ARMV7_CYCLE_COUNTER)
		val = ARMV7_INTENS_C;
	else
		val = ARMV7_INTENS_P(idx);

	asm volatile("mcr p15, 0, %0, c9, c14, 1" : : "r" (val));

	return idx;
}
