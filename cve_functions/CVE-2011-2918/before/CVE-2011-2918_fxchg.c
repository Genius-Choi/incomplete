static int fxchg(struct sh_fpu_soft_struct *fregs, int flag)
{
	FPSCR ^= flag;
	return 0;
}
