static int em_fnstsw(struct x86_emulate_ctxt *ctxt)
{
	u16 fsw;

	if (ctxt->ops->get_cr(ctxt, 0) & (X86_CR0_TS | X86_CR0_EM))
		return emulate_nm(ctxt);

	ctxt->ops->get_fpu(ctxt);
	asm volatile("fnstsw %0": "+m"(fsw));
	ctxt->ops->put_fpu(ctxt);

	ctxt->dst.val = fsw;

	return X86EMUL_CONTINUE;
}
