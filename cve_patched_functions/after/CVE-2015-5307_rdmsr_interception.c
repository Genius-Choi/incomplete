static int rdmsr_interception(struct vcpu_svm *svm)
{
	u32 ecx = kvm_register_read(&svm->vcpu, VCPU_REGS_RCX);
	struct msr_data msr_info;

	msr_info.index = ecx;
	msr_info.host_initiated = false;
	if (svm_get_msr(&svm->vcpu, &msr_info)) {
		trace_kvm_msr_read_ex(ecx);
		kvm_inject_gp(&svm->vcpu, 0);
	} else {
		trace_kvm_msr_read(ecx, msr_info.data);

		kvm_register_write(&svm->vcpu, VCPU_REGS_RAX,
				   msr_info.data & 0xffffffff);
		kvm_register_write(&svm->vcpu, VCPU_REGS_RDX,
				   msr_info.data >> 32);
		svm->next_rip = kvm_rip_read(&svm->vcpu) + 2;
		skip_emulated_instruction(&svm->vcpu);
	}
	return 1;
}
