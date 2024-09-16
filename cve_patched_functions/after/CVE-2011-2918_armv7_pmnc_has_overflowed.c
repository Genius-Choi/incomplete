static inline int armv7_pmnc_has_overflowed(unsigned long pmnc)
{
	return pmnc & ARMV7_OVERFLOWED_MASK;
}
