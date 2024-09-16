static inline int armv7_pmnc_select_counter(unsigned int idx)
{
	u32 val;

	if ((idx < ARMV7_COUNTER0) || (idx > ARMV7_COUNTER_LAST)) {
		pr_err("CPU%u selecting wrong PMNC counter"
			" %d\n", smp_processor_id(), idx);
		return -1;
	}

	val = (idx - ARMV7_EVENT_CNT_TO_CNTx) & ARMV7_SELECT_MASK;
	asm volatile("mcr p15, 0, %0, c9, c12, 5" : : "r" (val));
	isb();

	return idx;
}
