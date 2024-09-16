static inline unsigned int fps_regval(struct fpustate *f,
				      unsigned int insn_regnum)
{
	return f->regs[insn_regnum];
}
