static int check_rdpmc(struct x86_emulate_ctxt *ctxt)
{
	u64 cr4 = ctxt->ops->get_cr(ctxt, 4);
	u64 rcx = reg_read(ctxt, VCPU_REGS_RCX);

	if ((!(cr4 & X86_CR4_PCE) && ctxt->ops->cpl(ctxt)) ||
	    ctxt->ops->check_pmc(ctxt, rcx))
		return emulate_gp(ctxt, 0);

	return X86EMUL_CONTINUE;
}
