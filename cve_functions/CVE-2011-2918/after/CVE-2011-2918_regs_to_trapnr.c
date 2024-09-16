static int regs_to_trapnr(struct pt_regs *regs)
{
	return (regs->cp0_cause >> 2) & 0x1f;
}
