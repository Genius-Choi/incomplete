static inline unsigned long *fpd_regaddr(struct fpustate *f,
					 unsigned int insn_regnum)
{
	insn_regnum = (((insn_regnum & 1) << 5) |
		       (insn_regnum & 0x1e));

	return (unsigned long *) &f->regs[insn_regnum];
}
