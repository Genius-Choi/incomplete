fsub(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m, int n)
{
	BOTH_PRmn(ARITH_X, SUB);
	return 0;
}
