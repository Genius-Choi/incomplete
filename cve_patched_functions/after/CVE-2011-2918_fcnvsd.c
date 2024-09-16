static int fcnvsd(struct sh_fpu_soft_struct *fregs, int n)
{
	FP_DECL_EX;
	FP_DECL_S(Fn);
	FP_DECL_D(Fr);
	UNPACK_S(Fn, FPUL);
	FP_CONV(D, S, 2, 1, Fr, Fn);
	PACK_D(DRn, Fr);
	return 0;
}
