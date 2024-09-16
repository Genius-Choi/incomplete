static int rsm_load_state_32(struct x86_emulate_ctxt *ctxt, u64 smbase)
{
	struct desc_struct desc;
	struct desc_ptr dt;
	u16 selector;
	u32 val, cr0, cr4;
	int i;

	cr0 =                      GET_SMSTATE(u32, smbase, 0x7ffc);
	ctxt->ops->set_cr(ctxt, 3, GET_SMSTATE(u32, smbase, 0x7ff8));
	ctxt->eflags =             GET_SMSTATE(u32, smbase, 0x7ff4) | X86_EFLAGS_FIXED;
	ctxt->_eip =               GET_SMSTATE(u32, smbase, 0x7ff0);

	for (i = 0; i < 8; i++)
		*reg_write(ctxt, i) = GET_SMSTATE(u32, smbase, 0x7fd0 + i * 4);

	val = GET_SMSTATE(u32, smbase, 0x7fcc);
	ctxt->ops->set_dr(ctxt, 6, (val & DR6_VOLATILE) | DR6_FIXED_1);
	val = GET_SMSTATE(u32, smbase, 0x7fc8);
	ctxt->ops->set_dr(ctxt, 7, (val & DR7_VOLATILE) | DR7_FIXED_1);

	selector =                 GET_SMSTATE(u32, smbase, 0x7fc4);
	set_desc_base(&desc,       GET_SMSTATE(u32, smbase, 0x7f64));
	set_desc_limit(&desc,      GET_SMSTATE(u32, smbase, 0x7f60));
	rsm_set_desc_flags(&desc,  GET_SMSTATE(u32, smbase, 0x7f5c));
	ctxt->ops->set_segment(ctxt, selector, &desc, 0, VCPU_SREG_TR);

	selector =                 GET_SMSTATE(u32, smbase, 0x7fc0);
	set_desc_base(&desc,       GET_SMSTATE(u32, smbase, 0x7f80));
	set_desc_limit(&desc,      GET_SMSTATE(u32, smbase, 0x7f7c));
	rsm_set_desc_flags(&desc,  GET_SMSTATE(u32, smbase, 0x7f78));
	ctxt->ops->set_segment(ctxt, selector, &desc, 0, VCPU_SREG_LDTR);

	dt.address =               GET_SMSTATE(u32, smbase, 0x7f74);
	dt.size =                  GET_SMSTATE(u32, smbase, 0x7f70);
	ctxt->ops->set_gdt(ctxt, &dt);

	dt.address =               GET_SMSTATE(u32, smbase, 0x7f58);
	dt.size =                  GET_SMSTATE(u32, smbase, 0x7f54);
	ctxt->ops->set_idt(ctxt, &dt);

	for (i = 0; i < 6; i++) {
		int r = rsm_load_seg_32(ctxt, smbase, i);
		if (r != X86EMUL_CONTINUE)
			return r;
	}

	cr4 = GET_SMSTATE(u32, smbase, 0x7f14);

	ctxt->ops->set_smbase(ctxt, GET_SMSTATE(u32, smbase, 0x7ef8));

	return rsm_enter_protected_mode(ctxt, cr0, cr4);
}
