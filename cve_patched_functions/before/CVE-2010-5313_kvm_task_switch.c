int kvm_task_switch(struct kvm_vcpu *vcpu, u16 tss_selector, int reason,
		    bool has_error_code, u32 error_code)
{
	struct decode_cache *c = &vcpu->arch.emulate_ctxt.decode;
	int ret;

	init_emulate_ctxt(vcpu);

	ret = emulator_task_switch(&vcpu->arch.emulate_ctxt,
				   tss_selector, reason, has_error_code,
				   error_code);

	if (ret)
		return EMULATE_FAIL;

	memcpy(vcpu->arch.regs, c->regs, sizeof c->regs);
	kvm_rip_write(vcpu, vcpu->arch.emulate_ctxt.eip);
	kvm_x86_ops->set_rflags(vcpu, vcpu->arch.emulate_ctxt.eflags);
	kvm_make_request(KVM_REQ_EVENT, vcpu);
	return EMULATE_DONE;
}
