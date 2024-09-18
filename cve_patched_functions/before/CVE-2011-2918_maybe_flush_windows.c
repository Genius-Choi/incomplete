static inline void maybe_flush_windows(unsigned int rs1, unsigned int rs2,
				       unsigned int rd, int from_kernel)
{
	if (rs2 >= 16 || rs1 >= 16 || rd >= 16) {
		if (from_kernel != 0)
			__asm__ __volatile__("flushw");
		else
			flushw_user();
	}
}
