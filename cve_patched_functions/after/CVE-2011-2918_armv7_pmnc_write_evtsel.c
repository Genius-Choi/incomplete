static inline void armv7_pmnc_write_evtsel(unsigned int idx, u32 val)
{
	if (armv7_pmnc_select_counter(idx) == idx) {
		val &= ARMV7_EVTSEL_MASK;
		asm volatile("mcr p15, 0, %0, c9, c13, 1" : : "r" (val));
	}
}
