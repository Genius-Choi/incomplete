static int em_fnstcw(struct x86_emulate_ctxt *ctxt)
{
	u16 fcw;

	if (ctxt->ops->get_cr(ctxt, 0) & (X86_CR0_TS | X86_CR0_EM))
		return emulate_nm(ctxt);

	ctxt->ops->get_fpu(ctxt);
	asm volatile("fnstcw %0": "+m"(fcw));
	ctxt->ops->put_fpu(ctxt);

	ctxt->dst.val = fcw;

	return X86EMUL_CONTINUE;
}
