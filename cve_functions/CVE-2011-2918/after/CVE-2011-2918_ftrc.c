static int ftrc(struct sh_fpu_soft_struct *fregs, int n)
{
	FP_DECL_EX;

	if (FPSCR_PR)
		EMU_FTRC_X(D, DRn);
	else
		EMU_FTRC_X(S, FRn);

	return 0;
}
