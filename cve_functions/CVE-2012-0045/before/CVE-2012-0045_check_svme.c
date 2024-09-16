static int check_svme(struct x86_emulate_ctxt *ctxt)
{
	u64 efer;

	ctxt->ops->get_msr(ctxt, MSR_EFER, &efer);

	if (!(efer & EFER_SVME))
		return emulate_ud(ctxt);

	return X86EMUL_CONTINUE;
}
