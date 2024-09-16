static inline void armv7_pmnc_write(unsigned long val)
{
	val &= ARMV7_PMNC_MASK;
	isb();
	asm volatile("mcr p15, 0, %0, c9, c12, 0" : : "r"(val));
}
