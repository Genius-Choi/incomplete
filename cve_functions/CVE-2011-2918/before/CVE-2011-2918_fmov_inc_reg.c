fmov_inc_reg(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m,
	     int n)
{
	if (FPSCR_SZ) {
		FMOV_EXT(n);
		READ(FRn, Rm + 4);
		n++;
		READ(FRn, Rm);
		Rm += 8;
	} else {
		READ(FRn, Rm);
		Rm += 4;
	}

	return 0;
}
