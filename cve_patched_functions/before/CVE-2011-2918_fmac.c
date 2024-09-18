fmac(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m, int n)
{
	FP_DECL_EX;
	FP_DECL_S(Fr);
	FP_DECL_S(Ft);
	FP_DECL_S(F0);
	FP_DECL_S(Fm);
	FP_DECL_S(Fn);
	UNPACK_S(F0, FR0);
	UNPACK_S(Fm, FRm);
	UNPACK_S(Fn, FRn);
	FP_MUL_S(Ft, Fm, F0);
	FP_ADD_S(Fr, Fn, Ft);
	PACK_S(FRn, Fr);
	return 0;
}
