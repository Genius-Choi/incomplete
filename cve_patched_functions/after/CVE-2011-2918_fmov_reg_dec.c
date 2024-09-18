fmov_reg_dec(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m,
	     int n)
{
	if (FPSCR_SZ) {
		FMOV_EXT(m);
		Rn -= 8;
		WRITE(FRm, Rn + 4);
		m++;
		WRITE(FRm, Rn);
	} else {
		Rn -= 4;
		WRITE(FRm, Rn);
	}

	return 0;
}
