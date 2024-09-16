int kvm_arm_copy_reg_indices(struct kvm_vcpu *vcpu, u64 __user *uindices)
{
	unsigned int i;
	const u64 core_reg = KVM_REG_ARM64 | KVM_REG_SIZE_U64 | KVM_REG_ARM_CORE;
	int ret;

	for (i = 0; i < sizeof(struct kvm_regs) / sizeof(__u32); i++) {
		if (put_user(core_reg | i, uindices))
			return -EFAULT;
		uindices++;
	}

	ret = kvm_arm_copy_fw_reg_indices(vcpu, uindices);
	if (ret)
		return ret;
	uindices += kvm_arm_get_fw_num_regs(vcpu);

	ret = copy_timer_indices(vcpu, uindices);
	if (ret)
		return ret;
	uindices += NUM_TIMER_REGS;

	return kvm_arm_copy_sys_reg_indices(vcpu, uindices);
}
