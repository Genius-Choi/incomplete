fmov_idx_reg(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m,
	     int n)
{
	if (FPSCR_SZ) {
		FMOV_EXT(n);
		READ(FRn, Rm + R0 + 4);
		n++;
		READ(FRn, Rm + R0);
	} else {
		READ(FRn, Rm + R0);
	}

	return 0;
}
