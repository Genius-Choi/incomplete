fmov_reg_reg(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m,
	     int n)
{
	if (FPSCR_SZ) {
		FMOV_EXT(m);
		FMOV_EXT(n);
		DRn = DRm;
	} else {
		FRn = FRm;
	}

	return 0;
}
