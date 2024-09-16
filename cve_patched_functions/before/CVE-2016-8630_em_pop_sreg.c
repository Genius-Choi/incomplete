static int em_pop_sreg(struct x86_emulate_ctxt *ctxt)
{
	int seg = ctxt->src2.val;
	unsigned long selector;
	int rc;

	rc = emulate_pop(ctxt, &selector, 2);
	if (rc != X86EMUL_CONTINUE)
		return rc;

	if (ctxt->modrm_reg == VCPU_SREG_SS)
		ctxt->interruptibility = KVM_X86_SHADOW_INT_MOV_SS;
	if (ctxt->op_bytes > 2)
		rsp_increment(ctxt, ctxt->op_bytes - 2);

	rc = load_segment_descriptor(ctxt, (u16)selector, seg);
	return rc;
}
