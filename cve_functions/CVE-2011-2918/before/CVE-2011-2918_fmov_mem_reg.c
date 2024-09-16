fmov_mem_reg(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int m,
	     int n)
{
	if (FPSCR_SZ) {
		FMOV_EXT(n);
		READ(FRn, Rm + 4);
		n++;
		READ(FRn, Rm);
	} else {
		READ(FRn, Rm);
	}

	return 0;
}
