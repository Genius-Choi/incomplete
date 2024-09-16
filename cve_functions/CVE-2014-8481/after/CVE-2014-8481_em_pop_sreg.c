static int em_pop_sreg(struct x86_emulate_ctxt *ctxt)
{
	int seg = ctxt->src2.val;
	unsigned long selector;
	int rc;

	rc = emulate_pop(ctxt, &selector, ctxt->op_bytes);
	if (rc != X86EMUL_CONTINUE)
		return rc;

	if (ctxt->modrm_reg == VCPU_SREG_SS)
		ctxt->interruptibility = KVM_X86_SHADOW_INT_MOV_SS;

	rc = load_segment_descriptor(ctxt, (u16)selector, seg);
	return rc;
}
