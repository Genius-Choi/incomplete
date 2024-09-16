static void init_emulate_ctxt(struct kvm_vcpu *vcpu)
{
	struct decode_cache *c = &vcpu->arch.emulate_ctxt.decode;
	int cs_db, cs_l;

	cache_all_regs(vcpu);

	kvm_x86_ops->get_cs_db_l_bits(vcpu, &cs_db, &cs_l);

	vcpu->arch.emulate_ctxt.vcpu = vcpu;
	vcpu->arch.emulate_ctxt.eflags = kvm_x86_ops->get_rflags(vcpu);
	vcpu->arch.emulate_ctxt.eip = kvm_rip_read(vcpu);
	vcpu->arch.emulate_ctxt.mode =
		(!is_protmode(vcpu)) ? X86EMUL_MODE_REAL :
		(vcpu->arch.emulate_ctxt.eflags & X86_EFLAGS_VM)
		? X86EMUL_MODE_VM86 : cs_l
		? X86EMUL_MODE_PROT64 :	cs_db
		? X86EMUL_MODE_PROT32 : X86EMUL_MODE_PROT16;
	memset(c, 0, sizeof(struct decode_cache));
	memcpy(c->regs, vcpu->arch.regs, sizeof c->regs);
}
