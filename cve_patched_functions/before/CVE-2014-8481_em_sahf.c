static int em_sahf(struct x86_emulate_ctxt *ctxt)
{
	u32 flags;

	flags = EFLG_CF | EFLG_PF | EFLG_AF | EFLG_ZF | EFLG_SF;
	flags &= *reg_rmw(ctxt, VCPU_REGS_RAX) >> 8;

	ctxt->eflags &= ~0xffUL;
	ctxt->eflags |= flags | X86_EFLAGS_FIXED;
	return X86EMUL_CONTINUE;
}
