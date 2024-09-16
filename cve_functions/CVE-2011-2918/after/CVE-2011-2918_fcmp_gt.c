fcmp_gt(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m, int n)
{
	if (CMP(CMP) > 0)
		regs->sr |= 1;
	else
		regs->sr &= ~1;

	return 0;
}
