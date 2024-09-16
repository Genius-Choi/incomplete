fmov_reg_mem(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m,
	     int n)
{
	if (FPSCR_SZ) {
		FMOV_EXT(m);
		WRITE(FRm, Rn + 4);
		m++;
		WRITE(FRm, Rn);
	} else {
		WRITE(FRm, Rn);
	}

	return 0;
}
