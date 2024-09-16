static int flds(struct sh_fpu_soft_struct *fregs, int n)
{
	FPUL = FRn;
	return 0;
}
