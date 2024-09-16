static inline int perf_intr_is_nmi(struct pt_regs *regs)
{
#ifdef __powerpc64__
	return !regs->softe;
#else
	return 0;
#endif
}
