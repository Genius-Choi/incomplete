static inline unsigned long *__fetch_reg_addr_kern(unsigned int reg,
						   struct pt_regs *regs)
{
	BUG_ON(reg >= 16);
	BUG_ON(regs->tstate & TSTATE_PRIV);

	return &regs->u_regs[reg];
}
