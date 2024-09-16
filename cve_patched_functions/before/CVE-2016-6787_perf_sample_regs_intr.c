static void perf_sample_regs_intr(struct perf_regs *regs_intr,
				  struct pt_regs *regs)
{
	regs_intr->regs = regs;
	regs_intr->abi  = perf_reg_abi(current);
}
