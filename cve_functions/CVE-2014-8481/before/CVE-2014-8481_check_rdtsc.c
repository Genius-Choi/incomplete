static int check_rdtsc(struct x86_emulate_ctxt *ctxt)
{
	u64 cr4 = ctxt->ops->get_cr(ctxt, 4);

	if (cr4 & X86_CR4_TSD && ctxt->ops->cpl(ctxt))
		return emulate_ud(ctxt);

	return X86EMUL_CONTINUE;
}
