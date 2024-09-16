static int fneg(struct sh_fpu_soft_struct *fregs, int n)
{
	FRn ^= (1 << (_FP_W_TYPE_SIZE - 1));
	return 0;
}
