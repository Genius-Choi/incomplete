unsigned long kvm_arm_num_regs(struct kvm_vcpu *vcpu)
{
	return num_core_regs() + kvm_arm_num_sys_reg_descs(vcpu)
		+ kvm_arm_get_fw_num_regs(vcpu)	+ NUM_TIMER_REGS;
}
