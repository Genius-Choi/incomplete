static inline int cop1_64bit(struct pt_regs *xcp)
{
	if (cpu_has_fpu)
		return xcp->cp0_status & ST0_FR;
#ifdef CONFIG_64BIT
	return !test_thread_flag(TIF_32BIT_REGS);
#else
	return 0;
#endif
}
