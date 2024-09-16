static int fld1(struct sh_fpu_soft_struct *fregs, int n)
{
	FRn = (_FP_EXPBIAS_S << (_FP_FRACBITS_S - 1));
	return 0;
}
