id_fnmx(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, u16 code)
{
	int n = (code >> 8) & 0xf, m = (code >> 4) & 0xf, x = code & 0xf;
	return (fnmx[x])(fregs, regs, m, n);
}
