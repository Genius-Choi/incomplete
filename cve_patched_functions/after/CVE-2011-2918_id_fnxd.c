id_fnxd(struct sh_fpu_soft_struct *fregs, struct pt_regs *regs, int x, int n)
{
	return (fnxd[x])(fregs, n);
}
