static int em_popa(struct x86_emulate_ctxt *ctxt)
{
	int rc = X86EMUL_CONTINUE;
	int reg = VCPU_REGS_RDI;
	u32 val;

	while (reg >= VCPU_REGS_RAX) {
		if (reg == VCPU_REGS_RSP) {
			rsp_increment(ctxt, ctxt->op_bytes);
			--reg;
		}

		rc = emulate_pop(ctxt, &val, ctxt->op_bytes);
		if (rc != X86EMUL_CONTINUE)
			break;
		assign_register(reg_rmw(ctxt, reg), val, ctxt->op_bytes);
		--reg;
	}
	return rc;
}
