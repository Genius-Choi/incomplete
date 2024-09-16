static int flush_pending_x87_faults(struct x86_emulate_ctxt *ctxt)
{
	int rc;

	ctxt->ops->get_fpu(ctxt);
	rc = asm_safe("fwait");
	ctxt->ops->put_fpu(ctxt);

	if (unlikely(rc != X86EMUL_CONTINUE))
		return emulate_exception(ctxt, MF_VECTOR, 0, false);

	return X86EMUL_CONTINUE;
}
