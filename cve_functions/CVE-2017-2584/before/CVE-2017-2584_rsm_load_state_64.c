static int rsm_load_state_64(struct x86_emulate_ctxt *ctxt, u64 smbase)
{
	struct desc_struct desc;
	struct desc_ptr dt;
	u64 val, cr0, cr4;
	u32 base3;
	u16 selector;
	int i, r;

	for (i = 0; i < 16; i++)
		*reg_write(ctxt, i) = GET_SMSTATE(u64, smbase, 0x7ff8 - i * 8);

	ctxt->_eip   = GET_SMSTATE(u64, smbase, 0x7f78);
	ctxt->eflags = GET_SMSTATE(u32, smbase, 0x7f70) | X86_EFLAGS_FIXED;

	val = GET_SMSTATE(u32, smbase, 0x7f68);
	ctxt->ops->set_dr(ctxt, 6, (val & DR6_VOLATILE) | DR6_FIXED_1);
	val = GET_SMSTATE(u32, smbase, 0x7f60);
	ctxt->ops->set_dr(ctxt, 7, (val & DR7_VOLATILE) | DR7_FIXED_1);

	cr0 =                       GET_SMSTATE(u64, smbase, 0x7f58);
	ctxt->ops->set_cr(ctxt, 3,  GET_SMSTATE(u64, smbase, 0x7f50));
	cr4 =                       GET_SMSTATE(u64, smbase, 0x7f48);
	ctxt->ops->set_smbase(ctxt, GET_SMSTATE(u32, smbase, 0x7f00));
	val =                       GET_SMSTATE(u64, smbase, 0x7ed0);
	ctxt->ops->set_msr(ctxt, MSR_EFER, val & ~EFER_LMA);

	selector =                  GET_SMSTATE(u32, smbase, 0x7e90);
	rsm_set_desc_flags(&desc,   GET_SMSTATE(u32, smbase, 0x7e92) << 8);
	set_desc_limit(&desc,       GET_SMSTATE(u32, smbase, 0x7e94));
	set_desc_base(&desc,        GET_SMSTATE(u32, smbase, 0x7e98));
	base3 =                     GET_SMSTATE(u32, smbase, 0x7e9c);
	ctxt->ops->set_segment(ctxt, selector, &desc, base3, VCPU_SREG_TR);

	dt.size =                   GET_SMSTATE(u32, smbase, 0x7e84);
	dt.address =                GET_SMSTATE(u64, smbase, 0x7e88);
	ctxt->ops->set_idt(ctxt, &dt);

	selector =                  GET_SMSTATE(u32, smbase, 0x7e70);
	rsm_set_desc_flags(&desc,   GET_SMSTATE(u32, smbase, 0x7e72) << 8);
	set_desc_limit(&desc,       GET_SMSTATE(u32, smbase, 0x7e74));
	set_desc_base(&desc,        GET_SMSTATE(u32, smbase, 0x7e78));
	base3 =                     GET_SMSTATE(u32, smbase, 0x7e7c);
	ctxt->ops->set_segment(ctxt, selector, &desc, base3, VCPU_SREG_LDTR);

	dt.size =                   GET_SMSTATE(u32, smbase, 0x7e64);
	dt.address =                GET_SMSTATE(u64, smbase, 0x7e68);
	ctxt->ops->set_gdt(ctxt, &dt);

	r = rsm_enter_protected_mode(ctxt, cr0, cr4);
	if (r != X86EMUL_CONTINUE)
		return r;

	for (i = 0; i < 6; i++) {
		r = rsm_load_seg_64(ctxt, smbase, i);
		if (r != X86EMUL_CONTINUE)
			return r;
	}

	return X86EMUL_CONTINUE;
}
