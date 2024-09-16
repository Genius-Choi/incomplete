static int emulate_iret_real(struct x86_emulate_ctxt *ctxt)
{
	int rc = X86EMUL_CONTINUE;
	unsigned long temp_eip = 0;
	unsigned long temp_eflags = 0;
	unsigned long cs = 0;
	unsigned long mask = X86_EFLAGS_CF | X86_EFLAGS_PF | X86_EFLAGS_AF |
			     X86_EFLAGS_ZF | X86_EFLAGS_SF | X86_EFLAGS_TF |
			     X86_EFLAGS_IF | X86_EFLAGS_DF | X86_EFLAGS_OF |
			     X86_EFLAGS_IOPL | X86_EFLAGS_NT | X86_EFLAGS_RF |
			     X86_EFLAGS_AC | X86_EFLAGS_ID |
			     X86_EFLAGS_FIXED;
	unsigned long vm86_mask = X86_EFLAGS_VM | X86_EFLAGS_VIF |
				  X86_EFLAGS_VIP;

	/* TODO: Add stack limit check */

	rc = emulate_pop(ctxt, &temp_eip, ctxt->op_bytes);

	if (rc != X86EMUL_CONTINUE)
		return rc;

	if (temp_eip & ~0xffff)
		return emulate_gp(ctxt, 0);

	rc = emulate_pop(ctxt, &cs, ctxt->op_bytes);

	if (rc != X86EMUL_CONTINUE)
		return rc;

	rc = emulate_pop(ctxt, &temp_eflags, ctxt->op_bytes);

	if (rc != X86EMUL_CONTINUE)
		return rc;

	rc = load_segment_descriptor(ctxt, (u16)cs, VCPU_SREG_CS);

	if (rc != X86EMUL_CONTINUE)
		return rc;

	ctxt->_eip = temp_eip;

	if (ctxt->op_bytes == 4)
		ctxt->eflags = ((temp_eflags & mask) | (ctxt->eflags & vm86_mask));
	else if (ctxt->op_bytes == 2) {
		ctxt->eflags &= ~0xffff;
		ctxt->eflags |= temp_eflags;
	}

	ctxt->eflags &= ~EFLG_RESERVED_ZEROS_MASK; /* Clear reserved zeros */
	ctxt->eflags |= X86_EFLAGS_FIXED;
	ctxt->ops->set_nmi_mask(ctxt, false);

	return rc;
}
