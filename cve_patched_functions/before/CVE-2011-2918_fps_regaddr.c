static inline unsigned int *fps_regaddr(struct fpustate *f,
					unsigned int insn_regnum)
{
	return &f->regs[insn_regnum];
}
