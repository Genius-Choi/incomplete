int emulate_int_real(struct x86_emulate_ctxt *ctxt, int irq)
{
	int rc;

	invalidate_registers(ctxt);
	rc = __emulate_int_real(ctxt, irq);
	if (rc == X86EMUL_CONTINUE)
		writeback_registers(ctxt);
	return rc;
}
